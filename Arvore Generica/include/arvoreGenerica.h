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

typedef struct dado {
    char diretorio[MAX_CARACTERES];
} Dado;

typedef struct no {
    struct no *pai;
    struct no *irmaoAnterior;
    struct dado dado;
    struct no *primeiroFilho;
    struct no *proximoIrmao;
} No;

void imprimirMenu();

// FUNÇÕES DE CONTROLE DOS PONTEIROS

void liberarPonteiros(No *raiz);
int arvoreVazia(No *raiz);
int arvoreSemFilhos(No *raiz);

// FUNÇÕES PARA MANIPULAÇÃO DA ÁRVORE

No *entradaDados();

No *inserir(No *raiz, No *auxiliar);
No *procurar(No *raiz, char *procura);
No* excluir(No* raiz, No *exclusao);
int exibirAtual(No *raiz);
void exibirTudo (No *raiz, int nivel);

// FUNÇÕES PARA CONTROLE DOS MENUS

No *menuInserir(No *raiz);
void menuProcurar(No *raiz);
void menuExibir(No* raiz);
No *menuRenomear(No *raiz);
No *menuExcluir(No *raiz);

No *menuNavegar(No *raiz);
No *procurarDiretorio(No* auxiliar);
