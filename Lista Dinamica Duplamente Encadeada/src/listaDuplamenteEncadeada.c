#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "listaDuplamenteEncadeada.h"

struct no *inicio = NULL, *corrente = NULL, *auxiliar = NULL, *fim = NULL;

// ============================================================================
// FUNÇÕES PADRÕES PARA OS PROJETOS DE ESTRUTURA DE DADOS

// FUNÇÕES PARA ENTRADA DE DADOS

int lerInteiro(char *mensagem, int min, int max) {
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

double lerDecimal(char *mensagem, double min, double max) {
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

int isNull(void *ponteiro) {
    return (ponteiro == NULL);
}

void liberar(void **ponteiro) {
    free(*ponteiro);
    *ponteiro = NULL;
}

// ============================================================================

void imprimirMenu() {
    system("cls");
    printf("===============================================\n");
    printf("  **  LISTA DINÂMICA DUPLAMENTE ENCADEADA  **  \n");
    printf("===============================================\n\n");
}

int validarCodigo(int codigo) {
    no *atual = inicio;
    while (atual != NULL) {
        if (atual->codigo == codigo){
            return 1;
        }
        atual = atual->next;
    }
    return 0;
}

// FUNÇÕES DE CONTROLE DOS PONTEIROS

int listaVazia() {
    return isNull(inicio);
}

no* percorrerLista(){
    no *ponteiro = inicio;
    while(!isNull(ponteiro->next)){
        ponteiro = ponteiro->next;
    }
    return ponteiro;
}

void liberarPonteiros(){
    corrente = inicio;
    
    while (!isNull(corrente)){
        auxiliar = corrente;
        corrente = corrente->next;
        liberar((void**) &auxiliar);
    }

    inicio = corrente = auxiliar = NULL;
}

void limparPonteiros(){
    auxiliar = corrente = NULL;
}

// FUNÇÕES PARA MANIPULAÇÃO DA LISTA

void entradaDados(int inserir) {

    if (inserir){
        int codigo, codigoExiste;

        do {
            codigo = lerInteiro("Insira o seu código: ", 1, MAX_INT);
            codigoExiste = validarCodigo(codigo);

            if (codigoExiste) printf("\nCódigo já está em uso, tente novamente!\n");

        } while (codigoExiste);

        auxiliar->codigo = codigo;
    }
    
    strcpy(auxiliar->nome, lerString("\nDigite o seu nome: "));
    auxiliar->idade = lerInteiro("\nDigite sua idade: ", 0, MAX_INT);
}

int classificarDados() {
    if (auxiliar->codigo < corrente->codigo){
        inicio = auxiliar;
        auxiliar->next = corrente;
        corrente->back = auxiliar;
        auxiliar->back = NULL;
        return 2;
    }

    while (corrente->next != NULL){
        if (corrente->codigo <= auxiliar->codigo && corrente->next->codigo > auxiliar->codigo){
            corrente->next->back = auxiliar;
            auxiliar->next = corrente->next;
            corrente->next = auxiliar;
            auxiliar->back = corrente;
            return 3;
        }
        corrente = corrente->next;
    }

    auxiliar->next = NULL;
    corrente->next = auxiliar;
    auxiliar->back = corrente;
    fim = auxiliar;
    return 4;
}

int inserir() {
    corrente = inicio;

    if (listaVazia()){
        auxiliar->next = NULL;
        inicio = auxiliar;
        auxiliar->back = NULL;
        fim = inicio;
        return 1;
    }

    return classificarDados();
}

void exibir() {
    printf("\n===  -------------------------------------  ===\n");
    printf("Anterior: %p\n", corrente->back);
    printf("Ponteiro: %p\n", corrente);
    printf("Código: %i\n", corrente->codigo);
    printf("Nome: %s\n", corrente->nome);
    printf("Idade: %i\n", corrente->idade);
    printf("Posterior: %p\n", corrente->next);
}

void exibirTodos(int ordemCrescente) {
    if (ordemCrescente){
        corrente = inicio;
        while(!isNull(corrente)){
            exibir();
            corrente = corrente->next;
        }
    } else {
        corrente = fim;
        while(!isNull(corrente)){
            exibir();
            corrente = corrente->back;
        }
    }
}

int procurar(int procura) {
    if (procura - inicio->codigo <= fim->codigo - procura){

        corrente = inicio;
        while (!isNull(corrente)){
            if (corrente->codigo == procura){
                break;
            }
            corrente = corrente->next;
        }

    } else {

        corrente = fim;
        while (!isNull(corrente)){
            if (corrente->codigo == procura){
                break;
            }
            corrente = corrente->back;
        }

    }

    if (corrente == NULL) {
        return 0;
    }

    return 1;
}

void alterar() {
    strcpy(corrente->nome, auxiliar->nome);
    corrente->idade = auxiliar->idade;
    liberar((void**) &auxiliar);
}

void excluir() {
    if (corrente == inicio) {
        inicio = inicio->next;

        if (!isNull(inicio->next)) {
            inicio->back = NULL;
        }

        if (corrente == fim){
            fim = NULL;
        }
        
    } else {

        if (corrente == fim){
            fim = fim->back;
            fim->next = NULL;

        } else {
            auxiliar = corrente->back;
            auxiliar->next = corrente->next;
            corrente->next->back = auxiliar;
        }
    }

    liberar((void**) &corrente);
    return;
}

// FUNÇÕES PARA CONTROLE DOS MENUS

void menuInserir() {
    imprimirMenu();
    printf("---------------- Inserir Dados ----------------\n\n");

    auxiliar = (no*) malloc(sizeof(no));

    if (isNull(auxiliar)) {
        printf("Falha ao alocar memória!\n");
        getch();
        return;
    }

    entradaDados(1);

    int x = inserir();
    if (x == 1){
        printf("\nPrimeiro dado da lista inserido com sucesso!");
    } else {
        if (x == 2){
            printf("\nDado inserido com sucesso no começo da lista!");
        } else {
            if (x == 3){
                printf("\nDado inserido com sucesso no meio da lista!");
            } else {
                printf("\nDado inserido com sucesso no final da lista!");
            }
        }
    }
    

    getch();
    return;
}

void menuExibir() {
    imprimirMenu();
    printf("---------------- Exibir  Dados ----------------\n");

    if(listaVazia()){
        printf("\nNenhum dado para exibir!");
    } else {
        printf("\n   [0] Ordem Decrescente\n");
        printf("   [1] Ordem Crescente\n\n");
        int ordem = lerInteiro("Digite em que ordem os dados serão exibidos: ", 0, 1);
        
        exibirTodos(ordem);
    }
    
    getch();
    return;
}

void menuProcurar() {
    imprimirMenu();
    printf("--------------- Procurar  Dados ---------------\n\n");

    if (listaVazia()){
        printf("Não há nada cadastrado no sistema!");
        getch();
        return;
    }

    int procura;
    printf("Digite o código de quem deseja pesquisar: ");
    scanf("%i", &procura);

    if (!procurar(procura)){
        printf("\nCadastro não encontrado no sistema!");
    } else {
        printf("\nRegistro encontrado com sucesso!\n");
        exibir();
    }

    getch();
    return;
}

void menuAlterar() {
    imprimirMenu();
    printf("---------------- Alterar Dados ----------------\n\n");

    if (listaVazia()){
        printf("Não há nada cadastrado no sistema!");
        getch();
        return;
    }

    int procura;
    printf("Digite o código de quem deseja alterar: ");
    scanf("%i", &procura);

    if (!procurar(procura)){
        printf("\nCadastro não encontrado no sistema!");
    } else {
        auxiliar = (no*) malloc(sizeof(no));
        if (isNull(auxiliar)) {
            printf("Erro de alocação de memória!\n");
            getch();
            return NULL;
        }
        printf("\nDados Atuais: \n");
        exibir();

        printf("\nInsira os novos dados do cadastro!\n");
        entradaDados(0);

        alterar();
        printf("\nDados alterados com sucesso!\n");

        exibir();
    }

    getch();
    return;
}

void menuExcluir() {
    imprimirMenu();
    printf("---------------- Excluir Dados ----------------\n\n");

    if (listaVazia()){
        printf("Não há nada cadastrado no sistema!");
        getch();
        return;
    }

    int procura;
    printf("Digite o código de quem deseja excluir: ");
    scanf("%i", &procura);

    if (!procurar(procura)){
        printf("\nCadastro não encontrado no sistema!");
    } else {
        excluir();
        printf("\nDado removido com sucesso!");
    }

    getch();
    return;
}
