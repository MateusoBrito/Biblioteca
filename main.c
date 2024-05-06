#include "Functions.h"
#include "Front.h"
#include "BibliotecaLoader.h"
#include <stdio.h>


int main(){
    Hash *biblioteca;
    biblioteca = criaHash(26);

    // devolver livro

    lerArquivoLivros(BANCODEDADOS, biblioteca);

    menu();
    
    int acao = 0;
    while(acao != 6){
        fflush(stdin);
        printf("O que deseja fazer?\n");
        scanf("%d",&acao);

        Livro *auxiliar = (Livro*)malloc(sizeof(Livro));
        char genero[20];

        switch(acao){
            case 1:
                adicionaLivro_menu(biblioteca,auxiliar);
                break;
            case 2:
                buscaLivro_menu(biblioteca,auxiliar);
                break;
            case 3:
                alugarLivro_menu(biblioteca,auxiliar);
                break;
            case 4:
                devolverLivro_menu(biblioteca, auxiliar);
                break;
            case 5:
                removerLivro_menu(biblioteca,auxiliar);
                break;
            case 6:
                imprimeCatalogo(biblioteca);
                break;
            case 7:
                salvarMudancas(BANCODEDADOS, biblioteca);
                break;
            default:
                printf("Opcao nao existe!\n");
                break;
        }

        free(auxiliar);
        printf("=========================================\n");
    }

    return 0;
}