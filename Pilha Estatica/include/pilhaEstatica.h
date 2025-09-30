#pragma once

// ============================================================================
// DEFINIÇÕES E FUNÇÕES PADRÕES PARA OS PROJETOS DE ESTRUTURA DE DADOS

#define MIN_INT -2147483648
#define MAX_INT 2147483647

#define MIN_DOUBLE -1.797693e+308
#define MAX_DOUBLE 1.797693e+308

#define MAX_CARACTERES 256

// FUNÇÕES PARA ENTRADA DE DADOS

int lerInteiro(char *mensagem, int min, int max);
double lerDecimal(char *mensagem, double min, double max);
char *lerString(char *mensagem);

// FUNÇÕES PARA MANIPULAÇÃO DE PONTEIROS

int isNull(void *ponteiro);
void liberar(void **ponteiro);

// ============================================================================

#define MAX 100

typedef struct dados {
    int codigo;
    char nome[MAX_CARACTERES];
    int idade;
} Dado;

typedef struct pilha {
    int quantidade;
    Dado dados[MAX];
} Pilha;

void imprimirMenu();
int validarCodigo(int codigo, Pilha *p);

// FUNÇÕES DE CONTROLE DOS PONTEIROS

int pilhaVazia(Pilha *p);
int pilhaCheia(Pilha *p);
Pilha* criarPilha();

// FUNÇÕES PARA MANIPULAÇÃO DA PILHA

Dado entradaDados(Pilha *p);

Pilha *empilhar(Pilha *p, Dado entrada);
Pilha *desempilhar(Pilha *p);
void verTopo(Pilha *p);

// FUNÇÕES PARA CONTROLE DOS MENUS

Pilha *menuEmpilhar(Pilha *p);
Pilha *menuDesempilhar(Pilha *p);
void menuVerTopo(Pilha *p);

