#ifndef GENEROS_H
#define GENEROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"

typedef struct{
    AVL **tabela;
    int tam,qtd;
}Hash;

Hash* criaHash(int tamanho){
    Hash *h;
    h = (Hash*)malloc(tamanho*sizeof(Hash));
    if(h != NULL){
        h->tam = tamanho;
        h->qtd = 0;
        h->tabela = (AVL**)malloc(tamanho*sizeof(AVL*));
        if(h->tabela == NULL) return NULL;
        for(int i=0;i<tamanho;i++)
            h->tabela[i] = NULL;
    }
    return h;
}

void destroiHash(Hash *h){
    if(h!=NULL){
        for(int i=0;i<h->tam;i++){
            if(h->tabela[i] != NULL)
                destroiAVL(h->tabela[i]);
        }
    free(h->tabela);
    free(h);
    }
}

int chaveDivisao(int chave, int tam){
    return (chave&0x7FFFFFFF)%tam;
}

void inserirBancosdeDados(Livro *livro, FILE *fh){
    if (livro->nome[strlen(livro->nome) - 1] == '\n')
        livro->nome[strlen(livro->nome) - 1] = '\0';
    fprintf(fh, "%s", livro->nome);
    fprintf(fh,"%s","|");
    fprintf(fh, "%s", livro->autor);
}

//É responsável por ver qual o gênero do livro e inserir naquela estante
int insereLivro(Hash *h, Livro *livro, FILE *arquivo){
    if(h==NULL) return 0;
    int pos = livro->nome[0] - 'a';
    if(h->tabela[pos] == NULL)
        h->tabela[pos] = criaAVL();
    insereElem(h->tabela[pos], livro, arquivo);       
    h->qtd++;
    return 1;
}

void lerBancoDeDados(Hash *h, FILE *fh){
    char caractere;
    char palavra[50];
    int indice = 0;

    Livro *auxiliar = (Livro*)malloc(sizeof(Livro));
    if(auxiliar == NULL){
        printf("Erro: falha na alocação de memória.\n");
        return;
    }

    while((caractere = fgetc(fh)) != EOF){
        if(caractere == '|' || caractere == '\n'){
            palavra[indice] = '\0';
            if(caractere == '|'){
                strcpy(auxiliar->nome, palavra);
            } else if(caractere == '\n'){
                strcpy(auxiliar->autor, palavra);
                insereLivro(h,auxiliar,fh);
            }
            indice = 0;
        } else {
            palavra[indice++] = caractere;
        }
    }
    free(auxiliar);
}

//Busca a posicao de um livro e se ele esta no catalogo
int buscaLivro(Hash *h, Livro *livro){
    if(h==NULL) return 0;
    int pos = livro->nome[0] - 'a';
    if(h->tabela[pos] == NULL) return 0;
    return pesquisa(h->tabela[pos], livro);
}

//Atualiza a sua disponibilidade para mostrar que esta alugado
int alugarLivro(Hash *h, Livro *livro){
    if(h==NULL) return 0;
    int pos = livro->nome[0] - 'a';
    if(h->tabela[pos] == NULL) return 0;
    return alugaElem(h->tabela[pos], livro);
}

//Remove o livro do catalogo
int removeLivro(Hash *h, Livro *livro){
    if(h==NULL) return 0;
    int pos = livro->nome[0] - 'a';
    removeElem(h->tabela[pos], livro);
    h->qtd--;
    return 0;
}

//Tem a funca de imprimir todo o catalogo todo por ordem de generos
void imprimeCatalogo(Hash *h){
    if(h==NULL) return;
    for(int i=0;i<h->tam;i++){
        if(h->tabela[i] != NULL)
            imprime(h->tabela[i]);
    }
}
#endif