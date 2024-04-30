#ifndef FRONT_H
#define FRONT_H

#include <stdio.h>
#include "Functions.h"

void menu(){
    printf("========== A L E X A N D R I A ==========\n");
    printf("1. Adicionar livro\n");
    printf("2. Buscar livro\n");
    printf("3. Alugar livro\n");
    printf("4. Remover livro\n");
    printf("5. Imprimir catalogo\n");
    printf("6. Sair\n");
    printf("=========================================\n");
    return;
}

void adicionaLivro_menu(Hash *biblioteca, Livro *auxiliar){
    fflush(stdin);
    printf("Qual livro deseja adicionar?\n");
    printf("Titulo:");
    fgets(auxiliar->nome,40,stdin);
    auxiliar->nome[strcspn(auxiliar->nome, "\n")] = '\0';
    printf("Autor:");
    fgets(auxiliar->autor,40,stdin);
    auxiliar->autor[strcspn(auxiliar->autor, "\n")] = '\0';
                
    insereLivro(biblioteca, auxiliar);
    return;
}

void buscaLivro_menu(Hash *biblioteca, Livro *auxiliar){
    fflush(stdin);
    printf("Qual livro deseja buscar?\n");
    fgets(auxiliar->nome,40,stdin);
    auxiliar->nome[strcspn(auxiliar->nome, "\n")] = '\0';

    if(buscaLivro(biblioteca,auxiliar) == 1){
        printf("Temos o livro!\n");
        if(auxiliar->quantidade == 0)
            printf("Mas esta alugado!\n");
        } else
            printf("Nao temos o livro!\n");
    return;
}

void alugarLivro_menu(Hash *biblioteca, Livro *auxiliar){
    fflush(stdin);  
    printf("Qual livro deseja alugar?\n");
    printf("Titulo:");

    fgets(auxiliar->nome,40, stdin);
    auxiliar->nome[strcspn(auxiliar->nome, "\n")] = '\0';

    if(buscaLivro(biblioteca, auxiliar) == 1){
        if(auxiliar->quantidade  != 0)
            alugarLivro(biblioteca, auxiliar);
        else
            printf("O livro ja esta alugado!\n");
    } else
        printf("Nao temos o livro!\n");
    return;
}

void removerLivro_menu(Hash *biblioteca, Livro *auxiliar){
    fflush(stdin); 
    printf("Qual livro deseja remover?\n");
    printf("Titulo:");
    fgets(auxiliar->nome,40,stdin);
    auxiliar->nome[strcspn(auxiliar->nome, "\n")] = '\0';
    printf("Autor:");
    fgets(auxiliar->autor,40,stdin);
    auxiliar->autor[strcspn(auxiliar->autor, "\n")] = '\0';

    removeLivro(biblioteca, auxiliar);
    return;
}

#endif