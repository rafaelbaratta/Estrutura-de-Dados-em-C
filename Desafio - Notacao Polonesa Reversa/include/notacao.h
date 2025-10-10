#pragma once

#define MAX_BUFFER 256

typedef struct pilhaOp{
    struct pilhaOp *back;
    char operador;
    struct pilhaOp *next;
} PilhaOp;

typedef struct pilhaNum{
    struct pilhaNum *back;
    int numero;
    struct pilhaNum *next;
} PilhaNum;

extern const char operadores[];

// FUN��O PARA IMPRESS�O DO MENU

void imprimirMenu();

// FUN��ES PARA CONTROLE DA PILHA

PilhaOp *empilharOperador(PilhaOp *topo, char operador);
PilhaOp *desempilharOperador(PilhaOp *topo);
PilhaNum *empilharNumero(PilhaNum *topo, int numero);
PilhaNum *desempilharNumero(PilhaNum *topo);

// FUN��ES PARA CONTROLE DAS EXPRESS�ES

void lerExpressao(char *mensagem, char *expressao);
void limparEspacos(char *expressao);
int expressaoValida(char *expressao);

// FUN��ES PARA ORGANIZAR A EXPRESS�O

int prioridade(char operador);
void organizarExpressao(char *expressao);

// FUN��ES PARA CALCULAR A EXPRESS�O

int operacoes(int num1, int num2, char operador);
int calcular(char *expressao);
