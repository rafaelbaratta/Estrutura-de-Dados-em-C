#pragma once

// ============================================================================
// DEFINIÇÕES E FUNÇÕES PADRÕES PARA OS PROJETOS DE ESTRUTURA DE DADOS

#define MIN_INT -2147483648
#define MAX_INT 2147483647

// FUNÇÕES PARA ENTRADA DE DADOS

int lerInteiro(char *mensagem, int min, int max);

// FUNÇÕES PARA MANIPULAÇÃO DE PONTEIROS

int isNull(void *ponteiro);

// ============================================================================

typedef struct dado {
    int valor;
} Dado;

typedef struct no {
    struct dado dado;
    struct no *direita;
    struct no *esquerda;
} No;

void imprimirMenu();

// FUNÇÕES DE CONTROLE DOS PONTEIROS

void liberarPonteiros(No *raiz);
int arvoreVazia(No *raiz);

// FUNÇÕES PARA MANIPULAÇÃO DA ÁRVORE

No *entradaDados();

No *inserir(No *raiz, No *auxiliar);
No *procurar(No *raiz, int procura);
No *excluir(No *raiz, int exclusao);
void exibir(No *raiz);

No *menorDireita(No *corrente);

// FUNÇÕES PARA CONTROLE DOS MENUS

No *menuInserir(No *raiz);
void menuProcurar(No *raiz);
void menuExibir(No* raiz);
No *menuExcluir(No *raiz);

