#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <locale.h>
#include "notacao.h"

int main() {
    setlocale(LC_ALL, "portuguese");
    char expressao[MAX_BUFFER];

    do {
        imprimirMenu();
        printf("  --- Apenas números inteiros de um dígito ---  \n\n");
        lerExpressao("Digite uma expressão matemática: ", expressao);

        while (!expressaoValida(expressao)) {
            lerExpressao("Digite uma expressão válida: ", expressao);
        }

        organizarExpressao(expressao);
        printf("\nExpressão NPR: %s\n", expressao);
        printf("\nResultado: %lf\n", calcular(expressao));
        
        printf("\nDigite S para outra expressão ou qualquer tecla para encerrar o programa: ");

    } while (toupper(getch()) == 'S');
    return 0;
}

