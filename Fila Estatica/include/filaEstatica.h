#pragma once

// ============================================================================
// DEFINI��ES E FUN��ES PADR�ES PARA OS PROJETOS DE ESTRUTURA DE DADOS

#define MIN_INT -2147483648
#define MAX_INT 2147483647

#define MIN_DOUBLE -1.797693e+308
#define MAX_DOUBLE 1.797693e+308

#define MAX_CARACTERES 256

// FUN��ES PARA ENTRADA DE DADOS

int lerInteiro(char *mensagem, int min, int max);
double lerDecimal(char *mensagem, double min, double max);
char *lerString(char *mensagem);

// FUN��ES PARA MANIPULA��O DE PONTEIROS

int isNull(void *ponteiro);
void liberar(void **ponteiro);

// ============================================================================

#define MAX 100

typedef struct dados {
    int codigo;
    char nome[MAX_CARACTERES];
    int idade;
} Dado;

typedef struct fila {
    int quantidade;
    Dado dados[MAX];
} Fila;

void imprimirMenu();
int validarCodigo(int codigo, Fila *f);

// FUN��ES DE CONTROLE DOS PONTEIROS

int filaVazia(Fila *f);
int filaCheia(Fila *f);
Fila* criarFila();

// FUN��ES PARA MANIPULA��O DA FILA

Dado entradaDados(Fila *f);

Fila *enfileirar(Fila *f, Dado entrada);
Fila *desenfileirar(Fila *f);
void consultar(Fila *f);

// FUN��ES PARA CONTROLE DOS MENUS

Fila *menuEnfileirar(Fila *f);
Fila *menuDesenfileirar(Fila *f);
void menuConsultar(Fila *f);

