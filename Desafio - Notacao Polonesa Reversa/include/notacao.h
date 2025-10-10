#pragma once

#define MAX_BUFFER 256

typedef struct pilha{
    struct pilha *back;
    char operador;
    struct pilha *next;
} Pilha;

extern const char operadores[];

// FUNÇÃO PARA IMPRESSÃO DO MENU

void imprimirMenu();

// FUNÇÕES PARA CONTROLE DA PILHA

Pilha *empilhar(Pilha *topo, char operador);
Pilha *desempilhar(Pilha *topo);

// FUNÇÕES PARA CONTROLE DAS EXPRESSÕES

void lerExpressao(char *mensagem, char *expressao);
void limparEspacos(char *expressao);
int expressaoValida(char *expressao);

// FUNÇÕES PARA ORGANIZAR A EXPRESSÃO

int prioridade(char operador);
void organizarExpressao(char *expressao);
