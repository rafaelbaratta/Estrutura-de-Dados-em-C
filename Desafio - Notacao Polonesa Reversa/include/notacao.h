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

// FUNÇÃO PARA IMPRESSÃO DO MENU

void imprimirMenu();

// FUNÇÕES PARA CONTROLE DA PILHA

PilhaOp *empilharOperador(PilhaOp *topo, char operador);
PilhaOp *desempilharOperador(PilhaOp *topo);
PilhaNum *empilharNumero(PilhaNum *topo, int numero);
PilhaNum *desempilharNumero(PilhaNum *topo);

// FUNÇÕES PARA CONTROLE DAS EXPRESSÕES

void lerExpressao(char *mensagem, char *expressao);
void limparEspacos(char *expressao);
int expressaoValida(char *expressao);

// FUNÇÕES PARA ORGANIZAR A EXPRESSÃO

int prioridade(char operador);
void organizarExpressao(char *expressao);

// FUNÇÕES PARA CALCULAR A EXPRESSÃO

int operacoes(int num1, int num2, char operador);
int calcular(char *expressao);
