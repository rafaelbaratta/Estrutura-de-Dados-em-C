#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreBinaria.h"

// ============================================================================
// FUN«’ES PADR’ES PARA OS PROJETOS DE ESTRUTURA DE DADOS

// FUN«’ES PARA ENTRADA DE DADOS

int lerInteiro(char *mensagem, int min, int max){
    int valor;

    printf("%s", mensagem);
    do{
        while (scanf(" %i", &valor) != 1) {
            printf("\nErro, entrada inv·lida!\n%s", mensagem);
            setbuf(stdin, NULL);
        }
        setbuf(stdin, NULL);

        if(valor < min || valor > max){
            printf("\nO valor digitado deve estar entre %i e %i: ", min, max);
        }

    } while (valor < min || valor > max);

    return valor;
}

// FUN«’ES PARA MANIPULA«√O DE PONTEIROS

int isNull(void *ponteiro){
    return (ponteiro == NULL);
}

// ============================================================================

void imprimirMenu() {
    system("cls");
    printf("===============================================\n");
    printf("  ************  ¡RVORE  BIN¡RIA  ************  \n");
    printf("===============================================\n\n");
}

// FUN«’ES DE CONTROLE DOS PONTEIROS

void liberarPonteiros(No *raiz) {
    if (isNull(raiz)) {
        return;
    }

    liberarPonteiros(raiz->direita);
    liberarPonteiros(raiz->esquerda);

    free(raiz);
}

int arvoreVazia(No *raiz) {
    return isNull(raiz);
}

// FUN«’ES PARA MANIPULA«√O DA ¡RVORE

No *entradaDados() {
    No *auxiliar = (No*)malloc(sizeof(No));
    if (isNull(auxiliar)) {
        printf("Erro de alocaÁ„o de memÛria!\n");
        return NULL;
    }

    auxiliar->dado.valor = lerInteiro("Digite um valor para inserir na ·rvore: ", 0, 1000);

    auxiliar->direita = auxiliar->esquerda = NULL;

    return auxiliar;
}

No *inserir(No *raiz, No *auxiliar) {
    if (isNull(auxiliar)) {
        printf("\nErro ao inserir dado!\n");
        return raiz;
    }

    if (arvoreVazia(raiz)) {
        raiz = auxiliar;
        printf("\nDados inseridos com sucesso!");
        return raiz;
    }

    No *corrente = raiz;

    if (auxiliar->dado.valor == corrente->dado.valor) {
        printf("\nValor j· existe na ·rvore!\n");
        return raiz;
    } else {
        if (auxiliar->dado.valor > corrente->dado.valor) {
            corrente->direita = inserir(corrente->direita, auxiliar);
            return corrente;
        } else {
            corrente->esquerda = inserir(corrente->esquerda, auxiliar);
            return corrente;
        }
    }
}

No *procurar(No *raiz, int procura) {
    No *auxiliar = NULL;

    if (isNull(raiz)) {
        return NULL;
    }

    if (procura == raiz->dado.valor) {
        return raiz;
    }

    if (procura > raiz->dado.valor) {
        auxiliar = procurar(raiz->direita, procura);
    } else {
        auxiliar = procurar(raiz->esquerda, procura);
    }

    if (!isNull(auxiliar)) {
        return auxiliar;
    }
    
    return NULL;
}

void exibir(No *raiz) {
    if (isNull(raiz)) {
        return;
    }

    exibir(raiz->esquerda);
    printf("%i ", raiz->dado.valor);
    exibir(raiz->direita);
}

No *excluir(No *raiz, int valor) {
    if (isNull(raiz)) {
        return NULL;
    }

    if (valor > raiz->dado.valor) {
        raiz->direita = excluir(raiz->direita, valor);
    } else {
        if (valor < raiz->dado.valor) {
            raiz->esquerda = excluir(raiz->esquerda, valor);
        } else {

            if (isNull(raiz->direita)) {
                No *auxiliar = raiz->esquerda;
                free(raiz);
                return auxiliar;
            } else {
                if (isNull(raiz->esquerda)) {
                    No *auxiliar = raiz->direita;
                    free(raiz);
                    return auxiliar;
                }
            }

            No *auxiliar = menorDireita(raiz->direita);
            raiz->dado.valor = auxiliar->dado.valor;
            raiz->direita = excluir(raiz->direita, auxiliar->dado.valor);
        }
    } 
    return raiz;
}

No *menorDireita(No *corrente) {
    while (corrente->esquerda != NULL) {
        corrente = corrente->esquerda;
    }
    return corrente;
}

// FUN«’ES PARA CONTROLE DOS MENUS

No *menuInserir(No *raiz) {
    imprimirMenu();
    printf("---------------- Inserir Dados ----------------\n\n");

    No *auxiliar = entradaDados();
    raiz = inserir(raiz, auxiliar);

    getch();
    return raiz;
}

void menuProcurar(No *raiz) {
    imprimirMenu();
    printf("----------- Procurar Valor na ¡rvore ----------\n\n");

    if (arvoreVazia(raiz)){
        printf("N„o h· nenhum dado na ·rvore!");
        getch();
        return;
    }

    int procura = lerInteiro("Digite o valor que deseja procurar: ", 0, 1000);
    No *auxiliar = procurar(raiz, procura);

    if (isNull(auxiliar)) {
        printf("\nDado n„o encontrado na ·rvore!");
    } else {
        printf("\nDado encontrado na ·rvore!");
    }
    
    getch();
    return;
}

void menuExibir(No *raiz) {
    imprimirMenu();
    printf("-------------- Ver Toda a ¡rvore --------------\n\n");

    if (arvoreVazia(raiz)){
        printf("N„o h· nenhum dado na ·rvore!");
        getch();
        return;
    }

    exibir(raiz);
    printf("\n\nTodos os valores da ·rvore exibidos!");
    getch();
    return;
}

No *menuExcluir(No *raiz) {
    imprimirMenu();
    printf("----------- Excluir Valor da ¡rvore -----------\n\n");

    if (arvoreVazia(raiz)){
        printf("N„o h· nenhum dado na ·rvore!");
        getch();
        return raiz;
    }

    int procura = lerInteiro("Digite o valor que deseja excluir: ", 0, 1000);
    No *auxiliar = procurar(raiz, procura);

    if (isNull(auxiliar)) {
        printf("\nDado n„o encontrado na ·rvore!");
        getch();
        return raiz;
    }

    raiz = excluir(raiz, auxiliar->dado.valor);
    printf("\nDado excluÌdo com sucesso!\n");

    if (arvoreVazia(raiz)){
        printf("\n¡rvore vazia\n");
    } else {
        printf("\n¡rvore com valores atualizados:\n\n");
        exibir(raiz);
    }

    getch();
    return raiz;
}
