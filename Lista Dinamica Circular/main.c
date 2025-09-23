#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include "listaCircular.h"

int main() {
    setlocale(LC_ALL, "portuguese");
    int opcao = 0;

    do {
        limparPonteiros();
        imprimirMenu();
        printf("       [1] Inserir dados\n");
        printf("       [2] Exibir dados\n");
        printf("       [3] Procurar dados\n");
        printf("       [4] Alterar dados\n");
        printf("       [5] Remover dados\n\n");
        printf("       [0] Encerrar programa\n\n");
        printf("-----------------------------------------------\n\n");
        opcao = lerInteiro("Escolha uma das opções acima para executar: ", 0, 5);


        switch(opcao){
            case 1: menuInserir(); break;
            case 2: menuExibir(); break;
            case 3: menuProcurar(); break;
            case 4: menuAlterar(); break;
            case 5: menuExcluir(); break;
            case 0: break;
            default: printf("Opção inválida! Tente novamente!\n"); getch(); break;
        }

    } while (opcao);

    liberarPonteiros();
    return 0;
}
