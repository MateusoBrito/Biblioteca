#ifndef BASE_H
#define BASE_H


#include "Functions.h"
#include "AVL.h"
#include <stdio.h>


void inserirBancosdeDados(Livro *livro, FILE *fh){
    if (livro->nome[strlen(livro->nome) - 1] == '\n')
        livro->nome[strlen(livro->nome) - 1] = '\0';
    fprintf(fh, "%s", livro->nome);
    fprintf(fh,"%s","|");
    fprintf(fh, "%s", livro->autor);
}

void lerBancoDeDados(Hash *h, FILE *fh){
    char caractere;
    char palavra[50];
    int indice = 0;
    Livro *auxiliar = (Livro*)malloc(sizeof(Livro));
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
            palavra[indice] = caractere;
            indice++;
        }
    }
    free(auxiliar);
}

#endif