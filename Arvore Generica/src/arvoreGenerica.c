#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreGenerica.h"

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

// ============================================================================

void imprimirMenu() {
    system("cls");
    printf("===============================================\n");
    printf("  ************  ÁRVORE GENÉRICA  ************  \n");
    printf("===============================================\n\n");
}

// FUNÇÕES DE CONTROLE DOS PONTEIROS

void liberarPonteiros(No *raiz) {
    if (isNull(raiz)) {
        return;
    }

    liberarPonteiros(raiz->primeiroFilho);
    liberarPonteiros(raiz->proximoIrmao);

    free(raiz);
}

int arvoreVazia(No *raiz) {
    return isNull(raiz);
}

int arvoreSemFilhos(No *raiz) {
    return isNull(raiz->primeiroFilho);
}

// FUNÇÕES PARA MANIPULAÇÃO DA ÁRVORE

No *entradaDados() {
    No *auxiliar = (No*)malloc(sizeof(No));
    if (isNull(auxiliar)) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }

    char *tmp = lerString("Digite o nome do diretório: ");
    strcpy(auxiliar->dado.diretorio, tmp);
    free(tmp);

    auxiliar->irmaoAnterior = auxiliar->pai = auxiliar->primeiroFilho = auxiliar->proximoIrmao = NULL;

    return auxiliar;
}

No *inserir(No *raiz, No *auxiliar) {
    if (isNull(auxiliar)) {
        printf("\nErro ao criar diretório!\n");
        return raiz;
    }

    if (arvoreVazia(raiz)) {
        raiz = auxiliar;
        return raiz;
    }

    No *posicao = menuNavegar(raiz);

    if (arvoreSemFilhos(posicao)) {
        posicao->primeiroFilho = auxiliar;
        auxiliar->pai = posicao;
        return raiz;
    }

    posicao = posicao->primeiroFilho;

    while (posicao->proximoIrmao != NULL) {
        posicao = posicao->proximoIrmao;
    }

    posicao->proximoIrmao = auxiliar;
    auxiliar->irmaoAnterior = posicao;
    auxiliar->pai = posicao->pai;
    return raiz;
}

No *procurar(No *raiz, char *procura) {
    No *auxiliar = NULL;

    if (isNull(raiz)) {
        return NULL;
    }

    if (strcmp(raiz->dado.diretorio, procura) == 0) {
        return raiz;
    }

    auxiliar = procurar(raiz->primeiroFilho, procura);

    if (auxiliar != NULL) {
        return auxiliar;
    }

    auxiliar = procurar(raiz->proximoIrmao, procura);

    if (auxiliar != NULL) {
        return auxiliar;
    }

    return NULL;
}

No *excluir(No *raiz, No *exclusao) {
    if (raiz == exclusao) {
        liberarPonteiros(raiz);
        return NULL;
    }

    No *auxiliar = exclusao->pai;
    if (auxiliar->primeiroFilho == exclusao) {
        auxiliar->primeiroFilho = exclusao->proximoIrmao;
    }

    if (exclusao->irmaoAnterior != NULL) {
        auxiliar = exclusao->irmaoAnterior;
        auxiliar->proximoIrmao = exclusao->proximoIrmao;
    }

    if (exclusao->proximoIrmao != NULL) {
        auxiliar = exclusao->proximoIrmao;
        auxiliar->irmaoAnterior = exclusao->irmaoAnterior;
    }

    liberarPonteiros(exclusao);
    return raiz;
}

int exibirAtual(No *raiz) {
    if (arvoreVazia(raiz)) {
        return 0;
    }

    printf("Diretório Atual: %s\n\n", raiz->dado.diretorio);

    if (arvoreSemFilhos(raiz)) {
        return 0;
    }

    No *corrente = raiz->primeiroFilho;

    while (corrente != NULL) {
        printf("- %s\n", corrente->dado.diretorio);
        corrente = corrente->proximoIrmao;
    }

    return 1;
}

void exibirFamilia(No *filho) {
    No *corrente = filho;
    while (corrente != NULL) {
        printf("\n- %s\n", corrente->dado.diretorio);
        if (corrente->pai != NULL) {
            printf("^");
        }
        corrente = corrente->pai;
    }
}

void exibirTudo (No *raiz, int nivel) {
    if (arvoreVazia(raiz)) {
        return;
    }

    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }

    printf("- %s\n", raiz->dado.diretorio);

    exibirTudo(raiz->primeiroFilho, nivel + 1);
    exibirTudo(raiz->proximoIrmao, nivel);
}

// FUNÇÕES PARA CONTROLE DOS MENUS

No *menuInserir(No *raiz) {
    imprimirMenu();
    printf("---------------- Inserir Dados ----------------\n\n");

    No *auxiliar = entradaDados();
    raiz = inserir(raiz, auxiliar);

    printf("\nDados inseridos com sucesso!");

    getch();
    return raiz;
}

void menuExibir(No *raiz) {
    imprimirMenu();
    printf("-------------- Ver Toda a Árvore --------------\n\n");

    if (arvoreVazia(raiz)){
        printf("Não há nenhum dado na árvore!");
        getch();
        return;
    }

    exibirTudo(raiz, 0);
    printf("\nÁrvore completa exibida!");
    getch();
    return;
}

void menuProcurar(No *raiz) {
    imprimirMenu();
    printf("-------------- Procurar Diretório -------------\n\n");

    if (arvoreVazia(raiz)){
        printf("Não há nenhum dado na árvore!");
        getch();
        return;
    }

    char *procura = lerString("Digite o nome do diretório que deseja procurar: ");
    No *resultado = procurar(raiz, procura);
    free(procura);

    if (isNull(resultado)) {
        printf("\nDado não encontrado na árvore!");
        getch();
        return;
    }

    exibirFamilia(resultado);
    
    printf("\nCaminho completo exibido!");
    getch();
    return;
}

No *menuRenomear(No *raiz) {
    imprimirMenu();
    printf("-------------- Renomear Diretório -------------\n\n");

    if (arvoreVazia(raiz)){
        printf("Não há nenhum dado na árvore!");
        getch();
        return raiz;
    }

    char *procura = lerString("Procure o nome do diretório que deseja renomear: ");
    No *resultado = procurar(raiz, procura);
    free(procura);

    if (isNull(resultado)) {
        printf("\nDado não encontrado na árvore!");
        getch();
        return raiz;
    }
    
    exibirFamilia(resultado);
    
    char *tmp = lerString("\nDigite o novo nome do diretório: ");
    strcpy(resultado->dado.diretorio, tmp);
    free(tmp);

    exibirFamilia(resultado);
    printf("\nDiretório renomeado com sucesso!");

    getch();
    return raiz;
}

No *menuExcluir(No *raiz) {
    imprimirMenu();
    printf("-------------- Excluir Diretório --------------\n\n");

    if (arvoreVazia(raiz)){
        printf("Não há nenhum dado na árvore!");
        getch();
        return raiz;
    }

    char *procura = lerString("Procure o nome do diretório que deseja excluir: ");
    No *resultado = procurar(raiz, procura);
    free(procura);

    if (isNull(resultado)) {
        printf("\nDado não encontrado na árvore!");
        getch();
        return raiz;
    }
    
    exibirFamilia(resultado);
    
    int continuar;
    continuar = lerInteiro("\nDigite \"1\" para confirmar a exclusão ou \"0\" para cancelar: ", 0, 1);

    if (continuar){
        raiz = excluir(raiz, resultado);
        printf("\nDiretório excluído com sucesso!\n");
    } else {
        printf("\nExclusão cancelada!\n");
        getch();
        return raiz;
    }

    if (arvoreVazia(raiz)){
        printf("\nÁrvore vazia\n");
    } else {
        printf("\nÁrvore de diretórios atualizada:\n\n");
        exibirTudo(raiz, 0);
    }

    getch();
    return raiz;
}

No *menuNavegar(No *raiz) {
    int opcao;
    No *auxiliar = raiz;

    do {
        system("cls");
        printf("------------ Navegar nos Diretórios -----------\n\n");
        int arvoreComFilhos = exibirAtual(auxiliar);
        if (!arvoreComFilhos) {
            printf("- Árvore sem filhos\n");
        }

        printf("\n");
        int min = 1, max = 1;
        if (auxiliar != raiz) {
            printf("[0] Voltar\n");
            min = 0;
        }
        printf("[1] Inserir Filho\n");
        if (arvoreComFilhos) {
            printf("[2] Avançar\n");
            max = 2;
        }
        opcao = lerInteiro("\nEscolha uma das opções acima para executar: ", min, max);

        switch (opcao) {
            case 0: auxiliar = auxiliar->pai; break;
            case 1: return auxiliar;
            case 2: auxiliar = procurarDiretorio(auxiliar); break;
            default: break;
        }
    } while (opcao != 1);

    return auxiliar;
}

No *procurarDiretorio(No *auxiliar) {
    No *corrente = auxiliar->primeiroFilho;
    char procurar[MAX_CARACTERES];
    char *tmp = lerString("\nNome do diretório que deseja entrar: ");
    strcpy(procurar, tmp);
    free(tmp);

    while (corrente != NULL) {
        if (strcmp(corrente->dado.diretorio, procurar) == 0) {
            return corrente;
        }
        corrente = corrente->proximoIrmao;
    }

    printf("\nDiretório não encontrado!");
    getch();
    return auxiliar;
}
