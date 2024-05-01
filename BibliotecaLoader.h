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
}

#endif