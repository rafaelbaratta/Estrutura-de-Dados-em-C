#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "listaDuplamenteEncadeada.h"

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

char *lerString(char *mensagem){
    static char frase[MAX_CARACTERES];

    printf("%s", mensagem);
    setbuf(stdin, NULL);

    fgets(frase, sizeof(frase), stdin);
    frase[strcspn(frase, "\n")] = '\0';

    return frase;
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

struct no *inicio = NULL, *corrente = NULL, *auxiliar = NULL;

void imprimirMenu() {
    system("cls");
    printf("===============================================\n");
    printf("  **  LISTA DINÂMICA DUPLAMENTE ENCADEADA  **  \n");
    printf("===============================================\n\n");
}

int validarCodigo(int codigo) {
    no *atual = inicio;
    while (atual != NULL) {
        if (atual->codigo == codigo && atual != corrente){
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

void entradaDados(){

    int codigo, codigoExiste;
    do {
        codigo = lerInteiro("Insira o seu código: ", 0, MAX_INT);
        codigoExiste = validarCodigo(codigo);

        if (codigoExiste) printf("\nCódigo já está em uso, tente novamente!\n");

    } while (codigoExiste);

    auxiliar->codigo = codigo;
    strcpy(auxiliar->nome, lerString("\nDigite o seu nome: "));
    auxiliar->idade = lerInteiro("\nDigite sua idade: ", 0, MAX_INT);
}

void inserir() {
    auxiliar->next = NULL;

    if (listaVazia()){
        inicio = auxiliar;
        auxiliar->back = NULL;
        return;
    }

    corrente = percorrerLista();
    corrente->next = auxiliar;
    auxiliar->back = corrente;
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

int procurar(int procura) {
    corrente = inicio;
    while (!isNull(corrente)){
        if (corrente->codigo == procura){
            break;
        }
        corrente = corrente->next;
    }

    if (corrente == NULL) {
        return 0;
    }

    return 1;
}

void alterar() {
    corrente->codigo = auxiliar->codigo;
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
        
    } else {
        auxiliar = corrente->back;

        if (isNull(corrente->next)){
            auxiliar->next = NULL;

        } else {
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

    entradaDados();

    inserir();
    printf("\nDados inseridos com sucesso!");

    getch();
    return;
}

void menuExibir() {
    imprimirMenu();
    printf("---------------- Exibir  Dados ----------------\n");

    if(listaVazia()){
        printf("\nNenhum dado para exibir!");
    } else {
        corrente = inicio;
        while(!isNull(corrente)){
            exibir();
            corrente = corrente->next;
        }
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

    if (procurar(procura) == 0){
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

    if (procurar(procura) == 0){
        printf("\nCadastro não encontrado no sistema!");
    } else {
        auxiliar = (no*) malloc(sizeof(no));
        printf("\nInsira os novos dados do cadastro!\n\n");
        entradaDados();
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

    if (procurar(procura) == 0){
        printf("\nCadastro não encontrado no sistema!");
    } else {
        excluir();
        printf("\nDado removido com sucesso!");
    }

    getch();
    return;
}
