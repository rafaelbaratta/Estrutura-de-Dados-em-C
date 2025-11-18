#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include "arvoreBinaria.h"

int main() {
    setlocale(LC_ALL, "portuguese");
    No *raiz = NULL;
    int opcao = 0;

    do {
        imprimirMenu();
        printf("       [1] Inserir\n");
        printf("       [2] Procurar\n");
        printf("       [3] Exibir\n");
        printf("       [4] Excluir\n\n");
        printf("       [0] Encerrar programa\n\n");
        printf("-----------------------------------------------\n\n");
        opcao = lerInteiro("Escolha uma das opções acima para executar: ", 0, 4);

        switch(opcao){
            case 1: raiz = menuInserir(raiz); break;
            case 2: menuProcurar(raiz); break;
            case 3: menuExibir(raiz); break;
            case 4: raiz = menuExcluir(raiz); break;
            case 0: break;
            default: printf("Opção inválida! Tente novamente!\n"); getch(); break;
        }

    } while (opcao);

    liberarPonteiros(raiz);
    return 0;
}
