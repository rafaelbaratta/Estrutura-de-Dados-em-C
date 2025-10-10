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
        lerExpressao("Digite uma express�o matem�tica: ", expressao);

        while (!expressaoValida(expressao)) {
            lerExpressao("Digite uma express�o v�lida: ", expressao);
        }

        organizarExpressao(expressao);

        system("cls");
        printf("\n%s\n", expressao);
        
        printf("\nDigite S para outra express�o ou qualquer tecla para encerrar o programa: ");

    } while (getch() == 'S');
    return 0;
}

