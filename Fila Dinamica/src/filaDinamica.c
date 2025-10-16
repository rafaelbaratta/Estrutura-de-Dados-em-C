#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "filaDinamica.h"

No *inicio = NULL, *final = NULL;

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
    printf("  *************  FILA DIN�MICA  *************  \n");
    printf("===============================================\n\n");
}

int validarCodigo(int codigo) {
    if (filaVazia()){
        return 0;
    }

    No* auxiliar = inicio;

    while (auxiliar != NULL) {
        if (auxiliar->dado.codigo == codigo){
            return 1;
        }
        auxiliar = auxiliar->next;
    }

    return 0;
}

// FUN��ES DE CONTROLE DOS PONTEIROS

int filaVazia() {
    return isNull(inicio);
}

void liberarPonteiros() {
    struct no *auxiliar, *corrente;
    corrente = inicio;
    
    while (corrente != NULL){
        auxiliar = corrente;
        corrente = corrente->back;
        liberar((void**) &auxiliar);
    }

    inicio = final = NULL;
}

// FUN��ES PARA MANIPULA��O DA FILA

No* entradaDados() {
    No *auxiliar;
    auxiliar = (No*)malloc(sizeof(No));

    int codigo, codigoExiste;

    do {
        codigo = lerInteiro("Insira o seu c�digo: ", 1, MAX_INT);
        codigoExiste = validarCodigo(codigo);

        if (codigoExiste) printf("\nC�digo j� est� em uso, tente novamente!\n");

    } while (codigoExiste);

    auxiliar->dado.codigo = codigo;

    char* temp = lerString("\nDigite o seu nome: ");
    strcpy(auxiliar->dado.nome, temp);
    auxiliar->dado.idade = lerInteiro("\nDigite sua idade: ", 0, MAX_INT);

    return auxiliar;
}

void enfileirar(No* auxiliar) {
    auxiliar->back = auxiliar->next = NULL;

    if (inicio == NULL) {
        inicio = auxiliar;
        final = auxiliar;
        return;
    }

    final->next = auxiliar;
    auxiliar->back = final;
    final = auxiliar;
    auxiliar = NULL;

    return;
}

void desenfileirar() {
    if (inicio == final){
        liberar((void**) &inicio);
        liberar((void**) &final);
        return;
    }

    No* auxiliar;
    auxiliar = inicio;

    inicio = inicio->next;
    inicio->back = NULL;

    liberar((void**) &auxiliar);
    return;
}

void consultar() {
    printf("===  ----- Frente da Fila -----  ===\n");
    printf("C�digo: %i\n", inicio->dado.codigo);
    printf("Nome: %s\n", inicio->dado.nome);
    printf("Idade: %i\n", inicio->dado.idade);
}

void exibir() {
    No *auxiliar = inicio;
    int i = 1;
    while (auxiliar != NULL) {
        printf("===  ----- Cadastro %i -----  ===\n", i);
        printf("Anterior: %p\n", auxiliar->back);
        printf("Ponteiro: %p\n", auxiliar);
        printf("C�digo: %i\n", auxiliar->dado.codigo);
        printf("Nome: %s\n", auxiliar->dado.nome);
        printf("Idade: %i\n", auxiliar->dado.idade);
        printf("Posterior: %p\n", auxiliar->next);
        auxiliar = auxiliar->next;
        i++;
    }
}

// FUN��ES PARA CONTROLE DOS MENUS

void menuEnfileirar() {
    imprimirMenu();
    printf("-------------- Enfileirar  Dados --------------\n\n");

    enfileirar(entradaDados());

    printf("\nDados enfileirados com sucesso!");
    
    getch();
    return;
}

void menuDesenfileirar() {
    imprimirMenu();
    printf("------------- Desenfileirar Dados -------------\n\n");

    if (filaVazia()){
        printf("N�o h� nenhum dado na fila!");
        getch();
        return;
    }

    consultar();
    int continuar;
    continuar = lerInteiro("\nDigite \"1\" para confirmar a exclus�o ou \"0\" para cancelar: ", 0, 1);

    if (continuar){
        desenfileirar();
        printf("\nDados desenfileirados com sucesso!\n");
    } else {
        printf("\nExclus�o cancelada!\n");
    }
    
    getch();
    return;
}

void menuConsultar() {
    imprimirMenu();
    printf("----------- Consultar In�cio da Fila ----------\n\n");

    if (filaVazia()){
        printf("N�o h� nenhum dado na fila!");
        getch();
        return;
    }

    consultar();
    getch();
    return;
}

void menuExibir() {
    imprimirMenu();
    printf("---------------- Exibir  Dados ----------------\n\n");

    if (filaVazia()){
        printf("N�o h� nenhum dado na fila!");
        getch();
        return;
    }

    exibir();
    getch();
    return;
}

