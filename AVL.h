#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"
#define MAIOR(a, b) ((a > b) ? (a) : (b))

typedef struct Livro{
    char nome[50];
    char autor[20];
    int quantidade;
}Livro;

typedef struct NO{
    Livro livro;
    int fb, alt;
    struct NO* esq;
    struct NO* dir;
}NO;

typedef struct NO* AVL;

NO* alocarNO(){
    return (NO*)malloc(sizeof(NO));
}

void liberarNO(NO *q){
    free(q);
}

AVL *criaAVL(){
    AVL *raiz = (AVL*)malloc(sizeof(AVL));
    if(raiz!=NULL)
        *raiz = NULL;
    return raiz;
}

void destroiRec(NO *no){
    if(no == NULL) return;
    destroiRec(no->esq);
    destroiRec(no->dir);
    liberarNO(no);
    no == NULL;
}

void destroiAVL(AVL *raiz){
    if(raiz != NULL){
        destroiRec(*raiz);
        free(raiz);
    }
}

int estaVazia(AVL *raiz){
    if(raiz == NULL) return 0;
    return (*raiz == NULL);
}

//=====================================================================
//Calcular fator de balanceamento(fb)
int altura(NO *raiz){
    if(raiz==NULL) return 0;
    if(raiz->alt > 0)
        return raiz->alt;
    else{
        return MAIOR(altura(raiz->esq), altura(raiz->dir)) + 1;
    }
}

int FatorBalanceamento(NO *raiz){
    if(raiz==NULL) return 0;
    return altura(raiz->esq) - altura(raiz->dir);
}

//=====================================================================
//BALANCEAMENTO DA ARVORE


//---------------------------------------------------------------------
//Rotacao Simples
void RotacaoDireita(NO **raiz){
    NO *aux;
    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;

    //Arrumando alturas e Fatores de Balanceamento dos NOs afetados
    (*raiz)->alt = aux->alt = -1;
    aux->alt = altura(aux);
    (*raiz)->alt = altura(*raiz);
    aux->fb = FatorBalanceamento(aux);
    (*raiz)->fb = FatorBalanceamento(*raiz);

    *raiz = aux;
}

void RotacaoEsquerda(NO **raiz){
    NO *aux;
    aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;

    //Arrumando alturas e Fatores de Balanceamento dos NOs afetados
    (*raiz)->alt = aux->alt = -1;
    aux->alt = altura(aux);
    (*raiz)->alt = altura(*raiz);
    aux->fb = FatorBalanceamento(aux);
    (*raiz)->fb = FatorBalanceamento(*raiz);

    *raiz = aux;
}

//---------------------------------------------------------------------
//Rotacao Dupla
void RotacaoEsquerdaDireita(NO **raiz){
    NO *FilhoEsquerdo;
    NO *FilhoFilhoDireito;

    FilhoEsquerdo = (*raiz)->esq;
    FilhoFilhoDireito = FilhoEsquerdo->dir;

    FilhoEsquerdo->dir = FilhoFilhoDireito->esq;
    FilhoFilhoDireito->dir = *raiz;

    //Arrumando alturas e Fatores de Balanceamento dos NOs afetados
    (*raiz)->alt = FilhoEsquerdo->alt = FilhoFilhoDireito->alt = -1;
    FilhoEsquerdo->alt = altura(FilhoEsquerdo);
    FilhoFilhoDireito->alt = altura(FilhoFilhoDireito);
    (*raiz)->alt = altura(*raiz);
    FilhoEsquerdo->fb = FatorBalanceamento(FilhoEsquerdo);
    FilhoFilhoDireito->fb = FatorBalanceamento(FilhoFilhoDireito);
    (*raiz)->fb = FatorBalanceamento(*raiz);

    *raiz = FilhoFilhoDireito;
}

void RotacaoDireitaEsquerda(NO **raiz){
    NO *FilhoDireito;
    NO *FilhoFilhoEsquerdo;

    FilhoDireito = (*raiz)->dir;
    FilhoFilhoEsquerdo = FilhoDireito->esq;

    FilhoDireito->esq = FilhoFilhoEsquerdo->dir;
    FilhoFilhoEsquerdo->dir = FilhoDireito;

    (*raiz)->dir = FilhoFilhoEsquerdo->esq;
    FilhoFilhoEsquerdo->esq = *raiz;

    //Arrumando alturas e Fatores de Balanceamento dos NOs afetados
    (*raiz)->alt = FilhoDireito->alt = FilhoFilhoEsquerdo->alt = -1;
    FilhoDireito->alt = altura(FilhoDireito);
    FilhoFilhoEsquerdo->alt = altura(FilhoFilhoEsquerdo);
    (*raiz)->alt = altura(*raiz);
    FilhoDireito->fb = FatorBalanceamento(FilhoDireito);
    FilhoFilhoEsquerdo->fb = FatorBalanceamento(FilhoFilhoEsquerdo);
    (*raiz)->fb = FatorBalanceamento(*raiz);

    *raiz = FilhoFilhoEsquerdo;
}

void RotacaoEsquerdaDireita2(NO **raiz){
    RotacaoEsquerda(&(*raiz)->esq);
    RotacaoDireita(raiz);
}

void RotacaoDireitaEsquerda2(NO **raiz){
    RotacaoDireita(&(*raiz)->dir);
    RotacaoEsquerda(raiz);
}

//---------------------------------------------------------------------
//Funcoes auxiliares referentes a cada filho

void AuxiliarFilhoEsquerda(NO **raiz){
    NO *FilhoEsquerda;
    FilhoEsquerda = (*raiz)->esq;
    if(FilhoEsquerda->fb == +1)
        RotacaoDireita(raiz);
    else
        RotacaoEsquerdaDireita(raiz);
}

void AuxiliarFilhoDireita(NO **raiz){
    NO *FilhoDireita;
    FilhoDireita = (*raiz)->dir;
    if(FilhoDireita->fb == -1)
        RotacaoEsquerda(raiz);
    else
        RotacaoDireitaEsquerda(raiz);
}

//=====================================================================
int insereRec(NO **raiz, Livro *livro){
    int ok; //controle para as chamadas recursivas
    if(*raiz == NULL){
        NO *novo = alocarNO();
        if(novo == NULL) return 0;
        strcpy(novo->livro.nome, livro->nome);
        strcpy(novo->livro.autor, livro->autor);
        novo->fb = 0, novo->alt = 1;
        novo->esq = novo->dir = NULL;
        novo->livro.quantidade = 1;
        *raiz = novo;
        return 1;

    } else {
        if(strcmp((*raiz)->livro.nome, livro->nome)==0){
            (*raiz)->livro.quantidade++;
            ok = 0;
        }
        if(strcmp((*raiz)->livro.nome, livro->nome)>0){
            ok = insereRec(&(*raiz)->esq, livro);
            if(ok){
                switch ((*raiz)->fb){
                    case -1:
                        (*raiz)->fb = 0;
                        ok = 0;
                        break;
                    case 0:
                        (*raiz)->fb = 1;
                        (*raiz)->alt++;
                        break;
                    case 1:
                        AuxiliarFilhoEsquerda(raiz);
                        ok = 0;
                        break;
                }
            } 
        } else if(strcmp((*raiz)->livro.nome, livro->nome)<0){
            ok = insereRec(&(*raiz)->dir, livro);
            if(ok){
                switch ((*raiz)->fb){
                    case -1:
                        AuxiliarFilhoDireita(raiz);
                        ok = 0;
                        break;
                    case 0:
                        (*raiz)->fb = -1;
                        (*raiz)->alt++;
                        break;
                    case 1:
                        (*raiz)->fb = 0;
                        ok = 0;
                        break;
                }
            }
        }
    }
    return ok;
}

int insereElem(AVL *raiz, Livro *livro){
    if(raiz==NULL) return 0;
    return insereRec(raiz, livro);
}

int pesquisaRec(NO **raiz, Livro *livro){
    if(*raiz == NULL) return 0;
    if(strcmp((*raiz)->livro.nome, livro->nome) == 0){
        *livro = (*raiz)->livro;
        return 1;
    }
    if(strcmp((*raiz)->livro.nome, livro->nome) > 0)
        return pesquisaRec(&(*raiz)->esq, livro);
    if(strcmp((*raiz)->livro.nome, livro->nome) < 0)
        return pesquisaRec(&(*raiz)->dir, livro);
}

int pesquisa(AVL *raiz, Livro *livro){
    if(raiz == NULL) return 0;
    if(estaVazia(raiz)) return 0;
    return pesquisaRec(raiz, livro);
}
int alugaRec(NO **raiz, Livro *livro){
    if(*raiz == NULL) return 0;
    if(strcmp((*raiz)->livro.nome, livro->nome) == 0){
        (*raiz)->livro.quantidade--;
        return 1;
    }
    if(strcmp((*raiz)->livro.nome, livro->nome) > 0)
        return alugaRec(&(*raiz)->esq, livro);
    if(strcmp((*raiz)->livro.nome, livro->nome) < 0)
        return alugaRec(&(*raiz)->dir, livro);
}

int alugaElem(AVL *raiz, Livro *livro){
    if(raiz == NULL) return 0;
    if(estaVazia(raiz)) return 0;
    return alugaRec(raiz, livro);
}

int removeRec(NO **raiz, Livro *livro){
    if(*raiz == NULL) return 0;
    int ok; //controle para as chamadas recursivas
    if(strcmp((*raiz)->livro.nome, livro->nome) == 0){
        NO *aux;
        if((*raiz)->esq == NULL && (*raiz)->dir == NULL){
            //Caso 1 - NO sem filhos
            *raiz = NULL;
        } else if((*raiz)->esq == NULL){
            //Caso 2.1 - Possui apenas uma subarvore direita
            aux = *raiz;
            *raiz = (*raiz)->dir;
            liberarNO(aux);
        } else if((*raiz)->dir == NULL){
            //Caso 2.2 - Possui apenas uma subarvore esquerda
            aux = *raiz;
            *raiz = (*raiz)->esq;
            liberarNO(aux);
        } else {
            //Caso 3 - Possui as duas subarvores
            // Substituindo pelo NO com maior valor da subarvore esquerda
            NO *Filho = (*raiz)->esq;
            while(Filho->dir != NULL)
                Filho = Filho->dir;
            *raiz = Filho;
            Filho->livro = *livro;
            return removeRec(&(*raiz)->esq, livro);
        }
        return 1;
    } else if(strcmp((*raiz)->livro.nome, livro->nome) > 0){
        ok = removeRec(&(*raiz)->esq, livro);
        if(ok){
            switch((*raiz)->fb){
            case +1:
            case 0:
                (*raiz)->alt = -1;
                (*raiz)->alt = altura(*raiz);
                (*raiz)->fb = FatorBalanceamento(*raiz);
                break;
            case -1:
                AuxiliarFilhoDireita(raiz);
                break;
            
            default:
                break;
            }
        }
    } else {
        ok = removeRec(&(*raiz)->dir, livro);
        if(ok){
            switch((*raiz)->fb){
                case -1:
                case 0:
                    (*raiz)->alt = -1;
                    (*raiz)->alt = altura(*raiz);
                    (*raiz)->fb = FatorBalanceamento(*raiz);
                    break;
                case +1:
                    AuxiliarFilhoEsquerda(raiz);
                    break;
            }
        }
    }
    return ok;
}

int removeElem(AVL* raiz, Livro *livro){
    if(pesquisa(raiz, livro) != 1)
        return 0;
    return removeRec(raiz,livro);
}

void emOrdem(NO *raiz, int nivel){
    if(raiz != NULL){
        emOrdem(raiz->esq, nivel+1);
        printf("%s,%s\nQuantidade:%d\n", raiz->livro.nome, raiz->livro.autor, raiz->livro.quantidade);
        printf("-----------------------------------------\n");
        emOrdem(raiz->dir, nivel+1);
    }
}

void preOrdem(NO *raiz, int nivel){
    if(raiz != NULL){
        printf("%s, %s\nQuantidade:%d\n ", raiz->livro.nome, raiz->livro.autor, raiz->livro.quantidade);
        preOrdem(raiz->esq, nivel+1);
        preOrdem(raiz->dir, nivel+1);
    }
}

void posOrdem(NO *raiz, int nivel){
    if(raiz != NULL){
        posOrdem(raiz->esq, nivel+1);
        posOrdem(raiz->dir, nivel+1);
        printf("%s, %s\nQuantidade:%d\n ", raiz->livro.nome, raiz->livro.autor, raiz->livro.quantidade);
    }
}

void imprime(AVL *raiz){
    if(raiz == NULL) return;
    if(estaVazia(raiz)) return; 
    emOrdem(*raiz, 0);
    return;
}

#endif
