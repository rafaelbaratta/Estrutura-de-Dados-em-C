#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include "pilhaEstatica.h"

int main() {
    setlocale(LC_ALL, "portuguese");
    Pilha *p = criarPilha();
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
            case 1: p = menuEmpilhar(p); break;
            case 2: p = menuDesempilhar(p); break;
            case 3: menuVerTopo(p); break;
            case 0: break;
            default: printf("Opção inválida! Tente novamente!\n"); getch(); break;
        }

    } while (opcao);

    liberar((void**) &p);
    return 0;
}
