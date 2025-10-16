#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include "pilhaDinamica.h"

int main() {
    setlocale(LC_ALL, "portuguese");
    struct no* topo = NULL;
    int opcao = 0;

    do {
        imprimirMenu();
        printf("       [1] PUSH - Empilhar\n");
        printf("       [2] POP - Desempilhar\n");
        printf("       [3] TOP - Ver topo\n\n");
        printf("       [0] Encerrar programa\n\n");
        printf("-----------------------------------------------\n\n");
        opcao = lerInteiro("Escolha uma das opções acima para executar: ", 0, 3);


        switch(opcao){
            case 1: topo = menuEmpilhar(topo); break;
            case 2: topo = menuDesempilhar(topo); break;
            case 3: menuVerTopo(topo); break;
            case 0: break;
            default: printf("Opção inválida! Tente novamente!\n"); getch(); break;
        }

    } while (opcao);

    liberarPonteiros(topo);
    return 0;
}
