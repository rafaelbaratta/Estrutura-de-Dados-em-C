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

typedef struct dado {
    int codigo;
    char nome[MAX_CARACTERES];
    int idade;
} Dado;

typedef struct lista Lista;

void imprimirMenu();

// FUN��ES B�SICAS PARA MANIPULA��O DA LISTA

int listaCheia(Lista* li);
int listaVazia(Lista* li);
Lista* criarLista();

// FUN��ES DE INSER��O

int inserirComeco(Lista* li, Dado entrada);
int inserirMeio(Lista* li, Dado entrada, int posicao);
int inserirFinal(Lista* li, Dado entrada);

// OUTRAS FUN��ES

void exibir(Lista* li, int i);
int procurar(Lista* li, int codigo);
int alterar(Lista* li, int codigo, Dado entrada);
int remover(Lista* li, int codigo);

// FUN��ES PARA CONTROLE DOS MENUS

void menuInserir(Lista* li);
void menuExibir(Lista* li);
void menuProcurar(Lista* li);
void menuAlterar(Lista* li);
void menuRemover(Lista* li);
