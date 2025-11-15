#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "filaEstaticaCircular.h"

// ============================================================================
// FUNÇÕES PADRÕES PARA OS PROJETOS DE ESTRUTURA DE DADOS

// FUNÇÕES PARA ENTRADA DE DADOS

int lerInteiro(char *mensagem, int min, int max){
    int valor;

    printf("%s", mensagem);
    do{
        while (scanf(" %i", &valor) != 1) {
            printf("\nErro, entrada inválida!\n%s", mensagem);
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
            printf("\nErro, entrada inválida!\n%s", mensagem);
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

// FUNÇÕES PARA MANIPULAÇÃO DE PONTEIROS

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
    printf("  ********  FILA ESTÁTICA CIRCULAR  *********  \n");
    printf("===============================================\n\n");
}

int validarCodigo(int codigo, Fila *f) {
    if (filaVazia(f)){
        return 0;
    }

    for (int i = 0; i < f->quantidade; i++) {
        int posicao = (f->inicio + i) % MAX;
        if (f->dados[posicao].codigo == codigo){
            return 1;
        }
    }

    return 0;
}

// FUNÇÕES DE CONTROLE DOS PONTEIROS

int filaVazia(Fila *f) {
    return (f->quantidade == 0);
}

int filaCheia(Fila *f) {
    return (f->quantidade == MAX);
}

Fila *criarFila(){
    Fila *f = (Fila*) malloc(sizeof(Fila));
    if (isNull(f)) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }

    if(!isNull(f)){
        f->quantidade = 0;
        f->inicio = 0;
        f->fim = -1;
    }

    return f;
}

// FUNÇÕES PARA MANIPULAÇÃO DA FILA

Dado entradaDados(Fila *f) {
    Dado entrada;

    int codigo, codigoExiste;

    do {
        codigo = lerInteiro("Insira o seu código: ", 1, MAX_INT);
        codigoExiste = validarCodigo(codigo, f);

        if (codigoExiste) printf("\nCódigo já está em uso, tente novamente!\n");

    } while (codigoExiste);

    entrada.codigo = codigo;

    char *temp = lerString("\nDigite o seu nome: ");
    strcpy(entrada.nome, temp);
    entrada.idade = lerInteiro("\nDigite sua idade: ", 0, MAX_INT);

    return entrada;
}

Fila *enfileirar(Fila *f, Dado entrada) {
    f->fim = (f->fim + 1) % MAX;
    f->dados[f->fim] = entrada;
    f->quantidade ++;

    return f;
}

Fila *desenfileirar(Fila *f) {
    if (f->quantidade == 0) {
        return f;
    }

    f->quantidade --;
    f->inicio = (f->inicio + 1) % MAX;

    if (filaVazia(f)) {
        f->inicio = 0;
        f->fim = -1;
    }

    return f;
}

void consultar(Fila *f) {
    printf("===  ----- Frente da Fila -----  ===\n");
    printf("Código: %i\n", f->dados[f->inicio].codigo);
    printf("Nome: %s\n", f->dados[f->inicio].nome);
    printf("Idade: %i\n", f->dados[f->inicio].idade);
}

void exibir(Fila* f) {
    for (int i = 0; i < f->quantidade; i++) {
        int posicao = (f->inicio + i) % MAX; 
        printf("===  ----- Cadastro %i -----  ===\n", i + 1);
        printf("Código: %i\n", f->dados[posicao].codigo);
        printf("Nome: %s\n", f->dados[posicao].nome);
        printf("Idade: %i\n", f->dados[posicao].idade);
    }
}

// FUNÇÕES PARA CONTROLE DOS MENUS

Fila *menuEnfileirar(Fila *f) {
    imprimirMenu();
    printf("-------------- Enfileirar  Dados --------------\n\n");

    if (filaCheia(f)){
        printf("A fila não possui espaço para novos registros!");
        getch();
        return f;
    }

    f = enfileirar(f, entradaDados(f));

    printf("Dados enfileirados com sucesso!");
    
    getch();
    return f;
}

Fila *menuDesenfileirar(Fila *f) {
    imprimirMenu();
    printf("------------- Desenfileirar Dados -------------\n\n");

    if (filaVazia(f)){
        printf("Não há nenhum dado na fila!");
        getch();
        return f;
    }

    consultar(f);
    int continuar;
    continuar = lerInteiro("\nDigite \"1\" para confirmar a exclusão ou \"0\" para cancelar: ", 0, 1);

    if (continuar){
        f = desenfileirar(f);
        printf("\nDados desenfileirados com sucesso!\n");
    } else {
        printf("\nExclusão cancelada!\n");
    }
    
    getch();
    return f;
}

void menuConsultar(Fila *f) {
    imprimirMenu();
    printf("----------- Consultar Início da Fila ----------\n\n");

    if (filaVazia(f)){
        printf("Não há nenhum dado na fila!");
        getch();
        return;
    }

    consultar(f);
    getch();
    return;
}

void menuExibir(Fila *f) {
    imprimirMenu();
    printf("---------------- Exibir  Dados ----------------\n\n");

    if (filaVazia(f)){
        printf("Não há nenhum dado na fila!");
        getch();
        return;
    }

    exibir(f);
    getch();
    return;
}
