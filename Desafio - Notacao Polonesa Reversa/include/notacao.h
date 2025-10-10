#pragma once

#define MAX_BUFFER 256

typedef struct pilha{
    struct pilha *back;
    char operador;
    struct pilha *next;
} Pilha;

extern const char operadores[];

// FUN��O PARA IMPRESS�O DO MENU

void imprimirMenu();

// FUN��ES PARA CONTROLE DA PILHA

Pilha *empilhar(Pilha *topo, char operador);
Pilha *desempilhar(Pilha *topo);

// FUN��ES PARA CONTROLE DAS EXPRESS�ES

void lerExpressao(char *mensagem, char *expressao);
void limparEspacos(char *expressao);
int expressaoValida(char *expressao);

// FUN��ES PARA ORGANIZAR A EXPRESS�O

int prioridade(char operador);
void organizarExpressao(char *expressao);
