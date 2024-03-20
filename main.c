#include "Functions.h"
#include "AVL.h"
#include <stdio.h>


int main(){
    Hash *biblioteca;
    biblioteca = criaHash(26);

    FILE *fh;
    fh = fopen("DataBase","r+");
    if(fh == NULL)
        printf("Erro ao abrir o arquivo.\n");

    


    printf("========== A L E X A N D R I A ==========\n");
    printf("1. Adicionar livro\n");
    printf("2. Buscar livro\n");
    printf("3. Alugar livro\n");
    printf("4. Remover livro\n");
    printf("5. Imprimir catalogo\n");
    printf("6. Sair\n");
    printf("=========================================\n");
    
    int acao = 0;
    while(acao != 6){
        fflush(stdin);
        printf("O que deseja fazer?\n");
        scanf("%d",&acao);

        Livro *auxiliar = (Livro*)malloc(sizeof(Livro));
        char genero[20];

        switch(acao){
            case 1:
                fflush(stdin);
                printf("Qual livro deseja adicionar?\n");
                printf("Titulo:");
                fgets(auxiliar->nome,40,stdin);
                printf("Autor:");
                fgets(auxiliar->autor,40,stdin);
                
                insereLivro(biblioteca, auxiliar, fh);
                break;

            case 2:
                fflush(stdin);  
                printf("Qual livro deseja buscar?\n");
                fgets(auxiliar->nome,40,stdin);

                if(buscaLivro(biblioteca,auxiliar) == 1){
                    printf("Temos o livro!\n");
                    if(auxiliar->quantidade == 0)
                        printf("Mas esta alugado!\n");
                } else
                    printf("Nao temos o livro!\n");
                break;

            case 3:
                fflush(stdin);  
                printf("Qual livro deseja alugar?\n");
                printf("Titulo:");
                fgets(auxiliar->nome,40, stdin);
                if(buscaLivro(biblioteca, auxiliar) == 1){
                    if(auxiliar->quantidade  != 0)
                        alugarLivro(biblioteca, auxiliar);
                    else
                        printf("O livro ja esta alugado!\n");
                } else
                    printf("Nao temos o livro!\n");
                break;
                // assim a gente vai pegar os dados de quem quer alugar e dar um prazo
            case 4:
                fflush(stdin); 
                printf("Qual livro deseja remover?\n");
                printf("Titulo:");
                fgets(auxiliar->nome,40,stdin);
                printf("Autor:");
                fgets(auxiliar->autor,40,stdin);

                removeLivro(biblioteca, auxiliar);
                break;

            case 5:
                imprimeCatalogo(biblioteca);
                break;

            case 6:
                break; 

            default:
                printf("Opcao nao existe!\n");
                break;
        }

        free(auxiliar);
        printf("=========================================\n");
    }

    fclose(fh);

    return 0;
}