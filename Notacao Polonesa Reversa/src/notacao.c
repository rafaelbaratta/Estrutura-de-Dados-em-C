#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "notacao.h"

const char operadores[] = {'+', '-', '*', '/', '\0'};

// FUNÇÃO PARA IMPRESSÃO DO MENU

void imprimirMenu() {
    system("cls");
    printf("================================================\n");
    printf("  ********  NOTAÇÃO POLONESA REVERSA  ********  \n");
    printf("================================================\n\n");
}

// FUNÇÕES PARA CONTROLE DA PILHA

PilhaOp *empilharOperador(PilhaOp *topo, char operador) {
    PilhaOp* auxiliar = (PilhaOp*)malloc(sizeof(PilhaOp));
    if (isNull(auxiliar)) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }

    auxiliar->back = NULL;
    auxiliar->next = NULL;
    auxiliar->operador = operador;

    if (topo == NULL) {
        topo = auxiliar;
        return topo;
    }

    topo->next = auxiliar;
    auxiliar->back = topo;
    topo = auxiliar;
    return topo;
}

PilhaOp *desempilharOperador(PilhaOp *topo) {
    if (topo == NULL) {
        return topo;
    }

    PilhaOp* auxiliar = topo;

    if (topo->back != NULL) {
        topo = topo->back;
        topo->next = NULL;
        free(auxiliar);
    } else {
        free(topo);
        topo = NULL;
    }

    return topo;
}

PilhaNum *empilharNumero(PilhaNum *topo, double numero) {
    PilhaNum* auxiliar = (PilhaNum*)malloc(sizeof(PilhaNum));
    if (isNull(auxiliar)) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }
    
    auxiliar->back = NULL;
    auxiliar->next = NULL;
    auxiliar->numero = numero;

    if (topo == NULL) {
        topo = auxiliar;
        return topo;
    }

    topo->next = auxiliar;
    auxiliar->back = topo;
    topo = auxiliar;
    return topo;
}

PilhaNum *desempilharNumero(PilhaNum *topo) {
    if (topo == NULL) {
        return topo;
    }

    PilhaNum* auxiliar = topo;

    if (topo->back != NULL) {
        topo = topo->back;
        topo->next = NULL;
        free(auxiliar);
    } else {
        free(topo);
        topo = NULL;
    }

    return topo;
}

// FUNÇÕES PARA CONTROLE DAS EXPRESSÕES

void lerExpressao(char *mensagem, char *expressao) {
    char entrada[MAX_BUFFER];

    printf("%s", mensagem);
    setbuf(stdin, NULL);

    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';

    strcpy(expressao, entrada);
    limparEspacos(expressao);
    
    return;
}

void limparEspacos(char *expressao) {
    for (size_t i = 0; i < strlen(expressao); i++) {
        if (expressao[i] == ' '){
            for (size_t j = i; j < strlen(expressao); j++){
                expressao[j] = expressao[j + 1];
            }
        }
    }
}

int expressaoValida(char *expressao) {
    int ultimoFoiOperador = 0;
    int parentesesAbertura = 0;
    int parentesesFechamento = 0;
    for (size_t i = 0; i < strlen(expressao); i++) {
        if (!isdigit(expressao[i]) && expressao[i] != '(' && expressao[i] != ')') {
            if (ultimoFoiOperador) {
                return 0;
            }
            int operador = 0;
            for (size_t j = 0; j < strlen(operadores); j++) {
                if (expressao[i] == operadores[j]) {
                    operador = 1;
                    ultimoFoiOperador = 1;
                }
            }
            if (!operador) {
                return 0;
            }
        } else {
            ultimoFoiOperador = 0;
            if (expressao[i] == '(') {
                parentesesAbertura++;
            } else {
                if (expressao[i] == ')') {
                    if (parentesesAbertura > parentesesFechamento){
                        parentesesFechamento++;
                    } else {
                        return 0;
                    }
                }
            }
        }
    }
    if (parentesesAbertura != parentesesFechamento) {
        return 0;
    }
    return 1;
}

// FUNÇÕES PARA ORGANIZAR A EXPRESSÃO

int prioridade(char operador) {
    switch (operador) {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;        
        default: return 0;
    }
}

void organizarExpressao(char *expressao) {
    PilhaOp *topo = NULL;
    char expressaoOrganizada[MAX_BUFFER];
    int indiceExpressao = 0;

    for(size_t i = 0; i < strlen(expressao); i++){

        if(isalnum(expressao[i])){
            expressaoOrganizada[indiceExpressao] = expressao[i];
            indiceExpressao++;
            continue;
        }

        if(expressao[i] == '('){
            topo = empilharOperador(topo, expressao[i]);
        }

        if(expressao[i] == ')'){
            while(topo->operador != '('){
                expressaoOrganizada[indiceExpressao] = topo->operador;
                indiceExpressao++;
                topo = desempilharOperador(topo);
            }

            if(topo != NULL && topo->operador == '('){
                topo = desempilharOperador(topo);
            }
        }

        for(size_t j = 0; j < strlen(operadores); j++){
            if(expressao[i] == operadores[j]){
                if (topo != NULL){
                    while (topo != NULL && prioridade(expressao[i]) <= prioridade(topo->operador) && topo->operador != '(') {
                        expressaoOrganizada[indiceExpressao] = topo->operador;
                        indiceExpressao++;
                        topo = desempilharOperador(topo);
                    }
                }
                topo = empilharOperador(topo, expressao[i]);
                break;
            }
        }
    }

    while (topo != NULL) {
        expressaoOrganizada[indiceExpressao] = topo->operador;
        indiceExpressao++;
        topo = desempilharOperador(topo);
    }

    expressaoOrganizada[indiceExpressao] = '\0';

    strcpy(expressao, expressaoOrganizada);
    return;
}

// FUNÇÕES PARA CALCULAR A EXPRESSÃO

double operacoes(double num1, double num2, char operador) {
    switch (operador) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': 
            if (num2 == 0){
                printf("\nErro: Divisão por 0!\n");
                exit(0);
            }
            return num1 / num2;
        default: return 0;
    }
}

double calcular(char *expressao) {
    PilhaNum* topo = NULL;

    for (size_t i = 0; i < strlen(expressao); i++) {
        if (isdigit(expressao[i])) {
            topo = empilharNumero(topo, expressao[i] - '0');
            continue;
        }

        for (size_t j = 0; j < strlen(operadores); j++){
            if (expressao[i] == operadores[j]) {
                double num2 = topo->numero;
                topo = desempilharNumero(topo);
                double num1 = topo->numero;
                topo = desempilharNumero(topo);
                topo = empilharNumero(topo, operacoes(num1, num2, expressao[i]));
            }
        }
    }

    return topo->numero;
}
