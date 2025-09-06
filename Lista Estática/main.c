#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include "listaEstatica.h"

int main() {
    setlocale(LC_ALL, "portuguese");
    Lista* li = criarLista();
    int opcao = 0;

    do {
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
            case 1: menuInserir(li); break;
            case 2: menuExibir(li); break;
            case 3: menuProcurar(li); break;
            case 4: menuAlterar(li); break;
            case 5: menuRemover(li); break;
            case 0: break;
            default: printf("Opção inválida! Tente novamente!\n"); getch(); break;
        }

    } while (opcao);

    liberar((void**) &li);
    return 0;
}
