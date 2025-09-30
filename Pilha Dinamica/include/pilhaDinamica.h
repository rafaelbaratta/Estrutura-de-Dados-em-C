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

typedef struct dados {
    int codigo;
    char nome[MAX_CARACTERES];
    int idade;
} dados;

typedef struct no {
    struct no *back;
    struct dados dado;
    struct no *next;
} no;

void imprimirMenu();
int validarCodigo(int codigo, struct no* topo);

// FUNÇÕES DE CONTROLE DOS PONTEIROS

int pilhaVazia(struct no* topo);
void liberarPonteiros(struct no* topo);

// FUNÇÕES PARA MANIPULAÇÃO DA PILHA

struct no* entradaDados(struct no* pilha);

struct no* empilhar(struct no* pilha, struct no* auxiliar);
struct no* desempilhar(struct no* pilha);
void verTopo(struct no* pilha);

// FUNÇÕES PARA CONTROLE DOS MENUS

struct no* menuEmpilhar(struct no* pilha);
struct no* menuDesempilhar(struct no* pilha);
void menuVerTopo(struct no* pilha);

