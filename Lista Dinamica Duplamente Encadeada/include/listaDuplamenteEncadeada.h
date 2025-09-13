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

typedef struct no {
    struct no *back;
    int codigo;
    char nome[MAX_CARACTERES];
    int idade;
    struct no *next;
} no;

void imprimirMenu();
int validarCodigo(int codigo);

// FUN��ES DE CONTROLE DOS PONTEIROS

int listaVazia();
no* percorrerLista();
void liberarPonteiros();
void limparPonteiros();

// FUN��ES PARA MANIPULA��O DA LISTA

void entradaDados();

void inserir();
void exibir();
int procurar(int procura);
void alterar();
void excluir();

// FUN��ES PARA CONTROLE DOS MENUS

void menuInserir();
void menuExibir();
void menuProcurar();
void menuAlterar();
void menuExcluir();
