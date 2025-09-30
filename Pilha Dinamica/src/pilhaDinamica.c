#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "pilhaDinamica.h"

// ============================================================================
// FUN��ES PADR�ES PARA OS PROJETOS DE ESTRUTURA DE DADOS

// FUN��ES PARA ENTRADA DE DADOS

int lerInteiro(char *mensagem, int min, int max){
    int valor;

    printf("%s", mensagem);
    do{
        while (scanf(" %i", &valor) != 1) {
            printf("\nErro, entrada inv�lida!\n%s", mensagem);
            setbuf(stdin, NULL);
        }
        setbuf(stdin, NULL);

        if(valor < min || valor > max){
            printf("\nO valor digitado deve estar entre %i e %i: ", min, max);
        }

    } while (valor < min || valor > max);

    return valor;
}

double lerDecimal(char *mensagem, double min, double max){
    double valor;

    printf("%s", mensagem);
    do{
        while (scanf(" %lf", &valor) != 1) {
            printf("\nErro, entrada inv�lida!\n%s", mensagem);
            setbuf(stdin, NULL);
        }
        setbuf(stdin, NULL);

        if(valor < min || valor > max){
            printf("\nO valor digitado deve estar entre %lf e %lf: ", min, max);
        }

    } while (valor < min || valor > max);

    return valor;
}

char *lerString(char *mensagem) {
    char frase[MAX_CARACTERES];

    printf("%s", mensagem);
    setbuf(stdin, NULL);

    fgets(frase, sizeof(frase), stdin);
    frase[strcspn(frase, "\n")] = '\0';

    char *string = malloc(strlen(frase) + 1);
    if (string != NULL) {
        strcpy(string, frase);
    }

    return string;
}

// FUN��ES PARA MANIPULA��O DE PONTEIROS

int isNull(void *ponteiro){
    return (ponteiro == NULL);
}

void liberar(void **ponteiro){
    free(*ponteiro);
    *ponteiro = NULL;
}

// ============================================================================

void imprimirMenu() {
    system("cls");
    printf("===============================================\n");
    printf("  ************  PILHA  DIN�MICA  ************  \n");
    printf("===============================================\n\n");
}

int validarCodigo(int codigo, struct no* topo) {
    if (pilhaVazia(topo)){
        return 0;
    }

    no *atual = topo;
    
    while (atual != NULL){
        if (atual->dado.codigo == codigo){
            return 1;
        }
        atual = atual->back;
    }

    return 0;
}

// FUN��ES DE CONTROLE DOS PONTEIROS

int pilhaVazia(struct no* topo) {
    return isNull(topo);
}

void liberarPonteiros(struct no* topo) {
    struct no *auxiliar;
    
    while (topo != NULL){
        auxiliar = topo;
        topo = topo->back;
        liberar((void**) &auxiliar);
    }

    topo = auxiliar = NULL;
}

// FUN��ES PARA MANIPULA��O DA PILHA

struct no* entradaDados(struct no* pilha) {
    struct no *auxiliar;
    auxiliar = (no*)malloc(sizeof(no));

    int codigo, codigoExiste;

    do {
        codigo = lerInteiro("Insira o seu c�digo: ", 1, MAX_INT);
        codigoExiste = validarCodigo(codigo, pilha);

        if (codigoExiste) printf("\nC�digo j� est� em uso, tente novamente!\n");

    } while (codigoExiste);

    auxiliar->dado.codigo = codigo;

    strcpy(auxiliar->dado.nome, lerString("\nDigite o seu nome: "));
    auxiliar->dado.idade = lerInteiro("\nDigite sua idade: ", 0, MAX_INT);
    auxiliar->back = auxiliar->next = NULL;

    return auxiliar;
}

struct no* empilhar(struct no* pilha, struct no* auxiliar) {
    if (pilha == NULL){
        pilha = auxiliar;
        return pilha;
    }

    auxiliar->back = pilha;
    pilha->next = auxiliar;
    pilha = auxiliar;

    return pilha;
}

struct no* desempilhar(struct no* pilha) {
    if (pilha == NULL){
        return NULL;
    }

    struct no *auxiliar = pilha;
    if (pilha->back != NULL){
        pilha = pilha->back;
        pilha->next = NULL;
        free(auxiliar);
        return pilha;
    }
    free(auxiliar);
    pilha = NULL;
    return pilha;
}

void verTopo(struct no* pilha) {
    printf("===  ----- Topo da Pilha -----  ===\n");
    printf("Ponteiro: %p\n", pilha);
    printf("C�digo: %i\n", pilha->dado.codigo);
    printf("Nome: %s\n", pilha->dado.nome);
    printf("Idade: %i\n", pilha->dado.idade);
    printf("Anterior: %p\n", pilha->back);
    printf("Posterior: %p\n", pilha->next);
}

// FUN��ES PARA CONTROLE DOS MENUS

struct no* menuEmpilhar(struct no* pilha) {
    imprimirMenu();
    printf("--------------- Empilhar  Dados ---------------\n\n");

    struct no* auxiliar = entradaDados(pilha);
    pilha = empilhar(pilha, auxiliar);

    printf("Dados empilhados com sucesso!");

    return pilha;
}

struct no* menuDesempilhar(struct no* pilha) {
    imprimirMenu();
    printf("-------------- Desempilhar Dados --------------\n\n");

    if (pilhaVazia(pilha)){
        printf("N�o h� nenhum dado na pilha!");
        getch();
        return pilha;
    }

    verTopo(pilha);
    int continuar;
    continuar = lerInteiro("\nDigite \"1\" para confirmar a exclus�o ou \"0\" para cancelar: ", 0, 1);

    if (continuar){
        pilha = desempilhar(pilha);
        printf("\nDados desempilhados com sucesso!\n");
    } else {
        printf("\nExclus�o cancelada!\n");
    }
    
    getch();
    return pilha;
}

void menuVerTopo(struct no* pilha) {
    imprimirMenu();
    printf("-------------- Ver Topo da Pilha --------------\n\n");

    if (pilhaVazia(pilha)){
        printf("N�o h� nenhum dado na pilha!");
        getch();
        return;
    }

    verTopo(pilha);
    getch();
    return;
}

