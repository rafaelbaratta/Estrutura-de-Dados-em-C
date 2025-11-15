#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "listaDinamica.h"

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
    printf("================================================\n");
    printf("  ********  LISTA DINÂMICA ENCADEADA  ********  \n");
    printf("================================================\n\n");
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

// FUNÇÕES PARA GRAVAÇÃO E LEITURA DOS DADOS

int gravarDados(){
    FILE *arquivo_txt = fopen(ARQUIVO_TXT, "w");
    FILE *arquivo_dat = fopen(ARQUIVO_DAT, "wb");

    if (isNull(arquivo_dat) || isNull(arquivo_txt)){
        return 0;
    }

    auxiliar = corrente = inicio;
    while (corrente != NULL){
        fwrite(auxiliar, sizeof(no), 1, arquivo_dat);
        fprintf(arquivo_txt, "%i\n%s\n%i", corrente->codigo, corrente->nome, corrente->idade);
        corrente = corrente->next;
        liberar((void**) auxiliar);
        auxiliar = corrente;
    }

    fclose(arquivo_dat);
    fclose(arquivo_txt);
    return 1;
}

int recuperarDados(){
    FILE *arquivo_dat = fopen(ARQUIVO_DAT, "rb");

    if (isNull(arquivo_dat)){
        return 0;
    }

    corrente = (no*)malloc(sizeof(no));
    if (isNull(corrente)) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }

    while(fread(corrente, sizeof(no), 1 , arquivo_dat)){

        if (isNull(inicio)){
            inicio = auxiliar = corrente;
        } else {
            auxiliar->next = corrente;
            auxiliar = corrente;
        }

        corrente->next = NULL;
        corrente = NULL;
        corrente = (no*)malloc(sizeof(no));
        if (isNull(corrente)) {
            printf("Erro de alocação de memória!\n");
            return NULL;
        }
    }
    
    fclose(arquivo_dat);
    return 1;
}

// FUNÇÕES DE CONTROLE DOS PONTEIROS

int listaVazia() {
    return isNull(inicio);
}

no* percorrerLista(no *ponteiro){
    ponteiro = inicio;
    while(!isNull(ponteiro->next)){
        ponteiro = ponteiro->next;
    }
    return ponteiro;
}

no* percorrerAtePonteiro(no *percorre, no *limite){
    percorre = inicio;
    while(percorre->next != limite){
        percorre = percorre->next;
    }
    return percorre;
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

void classificacao(){
    corrente = inicio;
    if (auxiliar->codigo < inicio->codigo){
        inicio = auxiliar;
        auxiliar->next = corrente;
        return;
    }
    
    while (!isNull(corrente->next)){
        if (auxiliar->codigo >= corrente->codigo && auxiliar->codigo <= corrente->next->codigo){
            auxiliar->next = corrente->next;
            corrente->next = auxiliar;
            return;
        }

        corrente = corrente->next;
    }

    corrente->next = auxiliar;
    auxiliar->next = NULL;
    return;
}

void inserir() {
    if (listaVazia()){
        inicio = auxiliar;
        auxiliar->next = NULL;
        return;
    }

    classificacao();
}

void exibir() {
    printf("\n===  --------------------------------------  ===\n");
    printf("Ponteiro: %p\n", corrente);
    printf("Código: %i\n", corrente->codigo);
    printf("Nome: %s\n", corrente->nome);
    printf("Idade: %i\n", corrente->idade);
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

    auxiliar = corrente;
    corrente = percorrerAtePonteiro(corrente, auxiliar);
    corrente->next = corrente->next->next;

    classificacao();
}

void excluir() {
    if (corrente == inicio) {
        inicio = inicio->next;
        
    } else {
        auxiliar = inicio;
        auxiliar = percorrerAtePonteiro(auxiliar, corrente);

        if (isNull(corrente->next)){
            auxiliar->next = NULL;

        } else {
            auxiliar->next = corrente->next;
        }
    }

    liberar((void**) &corrente);
    return;
}

// FUNÇÕES PARA CONTROLE DOS MENUS

void menuInserir() {
    imprimirMenu();
    printf("---------------- Inserir  Dados ----------------\n\n");

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
    printf("----------------- Exibir Dados -----------------\n");

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
    printf("---------------- Procurar Dados ----------------\n\n");

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
    printf("---------------- Alterar  Dados ----------------\n\n");

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
        auxiliar = corrente;
        printf("\nInsira os novos dados do cadastro!\n\n");
        entradaDados();
        alterar();
        printf("\nDados alterados com sucesso!\n");
    }

    getch();
    return;
}

void menuExcluir() {
    imprimirMenu();
    printf("---------------- Excluir  Dados ----------------\n\n");

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
