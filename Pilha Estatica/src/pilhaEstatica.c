#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "pilhaEstatica.h"

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
    printf("  ************  PILHA  EST�TICA  ************  \n");
    printf("===============================================\n\n");
}

int validarCodigo(int codigo, Pilha *p) {
    if (pilhaVazia(p)){
        return 0;
    }

    Pilha *atual = p;
    
    for (int i = 0; i < p->quantidade; i++) {
        if (atual->dados[i].codigo == codigo){
            return 1;
        }
    }

    return 0;
}

// FUN��ES DE CONTROLE DOS PONTEIROS

int pilhaVazia(Pilha *p) {
    return (p->quantidade == 0);
}

int pilhaCheia(Pilha *p) {
    return (p->quantidade == MAX);
}

Pilha *criarPilha(){
    Pilha *p;
    p = (Pilha*) malloc(sizeof(Pilha));

    if(!isNull(p)){
        p->quantidade = 0;
    }

    return p;
}

// FUN��ES PARA MANIPULA��O DA PILHA

Dado entradaDados(Pilha *p) {
    Dado entrada;

    int codigo, codigoExiste;

    do {
        codigo = lerInteiro("Insira o seu c�digo: ", 1, MAX_INT);
        codigoExiste = validarCodigo(codigo, p);

        if (codigoExiste) printf("\nC�digo j� est� em uso, tente novamente!\n");

    } while (codigoExiste);

    entrada.codigo = codigo;

    strcpy(entrada.nome, lerString("\nDigite o seu nome: "));
    entrada.idade = lerInteiro("\nDigite sua idade: ", 0, MAX_INT);

    return entrada;
}

Pilha *empilhar(Pilha *p, Dado entrada) {
    p->dados[p->quantidade] = entrada;
    p->quantidade ++;

    return p;
}

Pilha *desempilhar(Pilha *p) {
    if (p->quantidade == 0){
        return p;
    }

    p->quantidade --;
    p->dados[p->quantidade].codigo = 0;
    strcpy(p->dados[p->quantidade].nome, "");
    p->dados[p->quantidade].idade = 0;
    
    return p;
}

void verTopo(Pilha *p) {
    printf("===  ----- Topo da Pilha -----  ===\n");
    printf("C�digo: %i\n", p->dados[p->quantidade-1].codigo);
    printf("Nome: %s\n", p->dados[p->quantidade-1].nome);
    printf("Idade: %i\n", p->dados[p->quantidade-1].idade);
}

// FUN��ES PARA CONTROLE DOS MENUS

Pilha *menuEmpilhar(Pilha *p) {
    imprimirMenu();
    printf("--------------- Empilhar  Dados ---------------\n\n");

    if (pilhaCheia(p)){
        printf("A pilha n�o possui espa�o para novos registros!");
        getch();
        return p;
    }

    p = empilhar(p, entradaDados(p));

    printf("\nDados empilhados com sucesso!");

    getch();
    return p;
}

Pilha *menuDesempilhar(Pilha *p) {
    imprimirMenu();
    printf("-------------- Desempilhar Dados --------------\n\n");

    if (pilhaVazia(p)){
        printf("N�o h� nenhum dado na pilha!");
        getch();
        return p;
    }

    verTopo(p);
    int continuar;
    continuar = lerInteiro("\nDigite \"1\" para confirmar a exclus�o ou \"0\" para cancelar: ", 0, 1);

    if (continuar){
        p = desempilhar(p);
        printf("\nDados desempilhados com sucesso!\n");
    } else {
        printf("\nExclus�o cancelada!\n");
    }
    
    getch();
    return p;
}

void menuVerTopo(Pilha *p) {
    imprimirMenu();
    printf("-------------- Ver Topo da Pilha --------------\n\n");

    if (pilhaVazia(p)){
        printf("N�o h� nenhum dado na pilha!");
        getch();
        return;
    }

    verTopo(p);
    getch();
    return;
}

