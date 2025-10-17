#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include "filaDinamica.h"

int main() {
    setlocale(LC_ALL, "portuguese");
    int opcao = 0;

    do {
        imprimirMenu();
        printf("       [1] Enfileirar\n");
        printf("       [2] Desenfileirar\n");
        printf("       [3] Consultar\n");
        printf("       [4] Exibir\n\n");
        printf("       [0] Encerrar programa\n\n");
        printf("-----------------------------------------------\n\n");
        opcao = lerInteiro("Escolha uma das opções acima para executar: ", 0, 4);


        switch(opcao){
            case 1: menuEnfileirar(); break;
            case 2: menuDesenfileirar(); break;
            case 3: menuConsultar(); break;
            case 4: menuExibir(); break;
            case 0: break;
            default: printf("Opção inválida! Tente novamente!\n"); getch(); break;
        }

    } while (opcao);

    liberarPonteiros();
    return 0;
}
