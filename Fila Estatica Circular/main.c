#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include "filaEstaticaCircular.h"

int main() {
    setlocale(LC_ALL, "portuguese");
    Fila *f = criarFila();
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
            case 1: f = menuEnfileirar(f); break;
            case 2: f = menuDesenfileirar(f); break;
            case 3: menuConsultar(f); break;
            case 4: menuExibir(f); break;
            case 0: break;
            default: printf("Opção inválida! Tente novamente!\n"); getch(); break;
        }

    } while (opcao);

    liberar((void**) &f);
    return 0;
}
