#ifndef BIBLIOTECALOADER_H
#define BIBLIOTECALOADER_H

#include <stdio.h>
#include "Functions.h"


void lerArquivoLivros(const char *nomeArquivo, Hash *biblioteca) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return;
    }

    char linha[50 + 20 + 2]; // Tamanho máximo da linha: título + autor + 1 espaço + \n
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *titulo = strtok(linha, ",");
        char *autor = strtok(NULL, "\n");

        
        // Remover espaços em branco desnecessários
        if (titulo[strlen(titulo) - 1] == ' ') titulo[strlen(titulo) - 1] = '\0';
        if (autor[0] == ' ') autor++;

        Livro *novoLivro = (Livro *)malloc(sizeof(Livro));
        if (novoLivro != NULL) {
            strcpy(novoLivro->nome, titulo);
            strcpy(novoLivro->autor, autor);
            insereLivro(biblioteca, novoLivro);
        } else {
            printf("Erro ao alocar memória para um novo livro.\n");
        }

    
    }

    fclose(arquivo);
    return;
}

void inserirLivroArquivo(NO *raiz, int nivel, FILE *arquivo){
    if(raiz != NULL){
        inserirLivroArquivo(raiz->esq, nivel+1, arquivo);
        for(int i=0; i<raiz->livro.quantidade;i++){
            fprintf(arquivo,"%s",raiz->livro.nome);
            fprintf(arquivo,",");
            fprintf(arquivo,"%s\n",raiz->livro.autor);
        }
        inserirLivroArquivo(raiz->dir, nivel+1, arquivo);
    }
}

void inserirLetraArquivo(AVL *raiz, FILE *arquivo){
    if(raiz == NULL) return;
    if(estaVazia(raiz)) return; 
    inserirLivroArquivo(*raiz, 0, arquivo);
    return;
}


void salvarMudancas(const char *nomeArquivo, Hash *biblioteca){
    FILE *arquivo = fopen(nomeArquivo,"w");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return;
    }

    for(int i=0;i<biblioteca->tam;i++){
        if(biblioteca->tabela[i] != NULL)
            inserirLetraArquivo(biblioteca->tabela[i], arquivo);
    }

    fclose(arquivo);
    return;
}

#endif