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

Pilha *empilhar(Pilha *topo, char operador) {
    Pilha* auxiliar = (Pilha*)malloc(sizeof(Pilha));
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

Pilha *desempilhar(Pilha *topo) {
    if (topo == NULL) {
        return topo;
    }

    Pilha* auxiliar = topo;

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
    for (size_t i = 0; i < strlen(expressao); i++) {
        if (!isalnum(expressao[i]) && expressao[i] != '(' && expressao[i] != ')') {
            int operador = 0;
            for (size_t j = 0; j < strlen(operadores); j++) {
                if (expressao[i] == operadores[j]) {
                    operador = 1;
                }
            }
            if (!operador) {
                return 0;
            }
        }
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
    Pilha *topo = NULL;
    char expressaoOrganizada[MAX_BUFFER];
    int indiceExpressao = 0;

    for(size_t i = 0; i < strlen(expressao); i++){

        if(isalnum(expressao[i])){
            expressaoOrganizada[indiceExpressao] = expressao[i];
            indiceExpressao++;
            continue;
        }

        if(expressao[i] == '('){
            topo = empilhar(topo, expressao[i]);
        }

        if(expressao[i] == ')'){
            while(topo->operador != '('){
                expressaoOrganizada[indiceExpressao] = topo->operador;
                indiceExpressao++;
                topo = desempilhar(topo);
            }

            if(topo != NULL && topo->operador == '('){
                topo = desempilhar(topo);
            }
        }

        for(size_t j = 0; j < strlen(operadores); j++){
            if(expressao[i] == operadores[j]){
                if (topo != NULL){
                    while (topo != NULL && prioridade(expressao[i]) <= prioridade(topo->operador) && topo->operador != '(') {
                        expressaoOrganizada[indiceExpressao] = topo->operador;
                        indiceExpressao++;
                        topo = desempilhar(topo);
                    }
                }
                topo = empilhar(topo, expressao[i]);
                break;
            }
        }
    }

    while (topo != NULL) {
        expressaoOrganizada[indiceExpressao] = topo->operador;
        indiceExpressao++;
        topo = desempilhar(topo);
    }

    expressaoOrganizada[indiceExpressao] = '\0';

    strcpy(expressao, expressaoOrganizada);
    return;
}
