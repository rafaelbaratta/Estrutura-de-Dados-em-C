#pragma once

// ============================================================================
// DEFINIÇÕES E FUNÇÕES PADRÕES PARA OS PROJETOS DE ESTRUTURA DE DADOS

#define MIN_INT -2147483648
#define MAX_INT 2147483647

#define MIN_DOUBLE -1.797693e+308
#define MAX_DOUBLE 1.797693e+308

#define MAX_CARACTERES 256

#define ARQUIVO_TXT "./data/dados.txt"
#define ARQUIVO_DAT "./data/dados.dat"

// FUNÇÕES PARA ENTRADA DE DADOS

int lerInteiro(char *mensagem, int min, int max);
double lerDecimal(char *mensagem, double min, double max);
char *lerString(char *mensagem);

// FUNÇÕES PARA MANIPULAÇÃO DE PONTEIROS

int isNull(void *ponteiro);
void liberar(void **ponteiro);

// ============================================================================

// FUNÇÕES PARA GRAVAÇÃO E LEITURA DOS DADOS

int gravarDados();
int recuperarDados();

typedef struct no {
    int codigo;
    char nome[MAX_CARACTERES];
    int idade;
    struct no *next;
} no;

void imprimirMenu();
int validarCodigo(int codigo);

// FUNÇÕES DE CONTROLE DOS PONTEIROS

int listaVazia();
no* percorrerLista(no* ponteiro);
no* percorrerAtePonteiro(no *percorre, no *limite);
void liberarPonteiros();
void limparPonteiros();

// FUNÇÕES PARA MANIPULAÇÃO DA LISTA

void entradaDados();

void classificacao();
void inserir();
void exibir();
int procurar(int procura);
void alterar();
void excluir();

// FUNÇÕES PARA CONTROLE DOS MENUS

void menuInserir();
void menuExibir();
void menuProcurar();
void menuAlterar();
void menuExcluir();