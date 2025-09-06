#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "listaEstatica.h"

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

struct lista {
    int quantidade;
    struct dado dados[MAX];
};

void imprimirMenu() {
    system("cls");
    printf("===============================================\n");
    printf("  ************  LISTA  ESTÁTICA  ************  \n");
    printf("===============================================\n\n");
}

// FUNÇÕES BÁSICAS PARA MANIPULAÇÃO DA LISTA

int listaCheia(Lista* li){
    return (li->quantidade == MAX);
}

int listaVazia(Lista* li){
    return (li->quantidade == 0);
}

Lista* criarLista(){
    Lista *li;
    li = (Lista*) malloc(sizeof(Lista));

    if(!isNull(li)){
        li->quantidade = 0;
    }

    return li;
}

// FUNÇÕES DE INSERÇÃO

int inserirComeco(Lista* li, Dado entrada){
    if (listaCheia(li) || isNull(li)) return 0;

    for (int i = li->quantidade; i >= 0; i--){
        li->dados[i + 1] = li->dados[i];
    }

    li->dados[0] = entrada;
    li->quantidade++;
    return 1;
}

int inserirMeio(Lista* li, Dado entrada, int posicao){
    if (listaCheia(li) || isNull(li)) return 0;

    for (int i = li->quantidade; i >= posicao; i--){
        li->dados[i + 1] = li->dados[i];
    }

    li->dados[posicao] = entrada;
    li->quantidade++;
    return 1;
}

int inserirFinal(Lista* li, Dado entrada){
    if (listaCheia(li) || isNull(li)) return 0;

    li->dados[li->quantidade] = entrada;
    li->quantidade++;
    return 1;
}

// OUTRAS FUNÇÕES

void exibir(Lista* li, int i){
    printf("== --------------------  ==\n");
    printf("\nPosição : %i", i);
    printf("\nCódigo : %i", li->dados[i].codigo);
    printf("\nNome : %s", li->dados[i].nome);
    printf("\nIdade : %i\n", li->dados[i].idade);
}

int procurar(Lista* li, int codigo){
    for (int i = 0; i < li->quantidade; i++) {
        if (codigo == li->dados[i].codigo){
            return i;
        }
    }
    
    return -1;
}

int alterar(Lista* li, int codigo, Dado entrada){
    int posicao = procurar(li, codigo);

    if (listaVazia(li) || isNull(li)) return 0;
    if (posicao == -1) return -1;

    li->dados[posicao] = entrada;
    return 1;
}

int remover(Lista* li, int codigo){
    int posicao = procurar(li, codigo);

    if (listaVazia(li) || isNull(li)) return 0;
    if (posicao == -1) return -1;

    for (int i = posicao; i < li->quantidade - 1; i++){
        li->dados[i] = li->dados[i + 1];
    }
    
    li->quantidade--;
    return 1;
}

// FUNÇÕES PARA CONTROLE DOS MENUS

void menuInserir(Lista* li){
    Dado entrada;
    int posicao;
    imprimirMenu();
    printf("---------------- Inserir Dados ----------------\n\n");

    if (listaCheia(li)){
        printf("Impossível adicionar novos dados, a lista já está cheia!\n\n");
        getch();
        return;
    }

    if (li->quantidade > 0){
        posicao = lerInteiro("Digite a posição que deseja inserir o dado: ", 0, MAX);
        if (posicao > li->quantidade){
            posicao = li->quantidade;
        }
        printf("\n");
    } else {
        posicao = li->quantidade;
    }

    int validar;
    do {
        entrada.codigo = lerInteiro("Insira o código do usuário: ", 0, MAX_INT);
        validar = procurar(li, entrada.codigo);

        if (validar != -1) printf("\nCódigo já está em uso, tente novamente!");

    } while (validar != -1);
    
    strcpy(entrada.nome, lerString("\nInsira o seu nome: "));
    entrada.idade = lerInteiro("\nInsira a sua idade: ", 0, MAX_INT);

    int x;
    if (posicao == 0) {
        x = inserirComeco(li, entrada);
    } else {
        if (posicao == li->quantidade) {
            x = inserirFinal(li, entrada);
        } else {
            x = inserirMeio(li, entrada, posicao);
        }
    }

    if (x == 0){
        printf("\nImpossível adicionar novos dados, a lista já está cheia!\n\n");
    } else {
        printf("\nDados adicionados com sucesso!\n\n");
    }

    getch();
    return;
}

void menuExibir(Lista* li){
    imprimirMenu();
    printf("---------------- Exibir  Dados ----------------\n\n");

    if (listaVazia(li)) {
        printf("Não há nada para exibir, pois a lista está vazia!\n\n");
    } else {
        for (int i = 0; i < li->quantidade; i++){
            exibir(li, i);
        }
    }

    getch();
    return;
}

void menuProcurar(Lista* li){
    imprimirMenu();
    printf("--------------- Procurar  Dados ---------------\n\n");

    if (listaVazia(li)){
        printf("Não há nada para procurar, pois a lista está vazia!\n\n");
        getch();
        return;
    }

    int codigo = lerInteiro("Digite o código de quem deseja procurar: ", 0, MAX_INT);

    int posicao = procurar(li, codigo);

    if (posicao == -1){
        printf("\nNão foi possível encontrar o usuário indicado!\n\n");
    } else {
        exibir(li, posicao);
    }

    getch();
    return;
}

void menuAlterar(Lista* li){
    Dado entrada;
    imprimirMenu();
    printf("---------------- Alterar Dados ----------------\n\n");

    if (listaVazia(li)){
        printf("Não há nada para alterar, pois a lista está vazia!\n\n");
        getch();
        return;
    }

    entrada.codigo = lerInteiro("Digite o código de quem deseja alterar: ", 0, MAX_INT);

    if (procurar(li, entrada.codigo) == -1){
        printf("\nNão foi possível encontrar o usuário indicado!\n\n");
        getch();
        return;
    }

    strcpy(entrada.nome, lerString("\nInsira o novo nome: "));
    entrada.idade = lerInteiro("\nInsira a nova idade: ", 0, MAX_INT);

    int x = alterar(li, entrada.codigo, entrada);

    if (x == -1){
        printf("\nNão foi possível encontrar o usuário indicado!\n\n");
    } else {
        if (x == 0){
            printf("\nNão há nada para alterar, pois a lista está vazia!\n\n");
        } else {
            printf("\nDados alterados com sucesso!\n\n");
        }
    }

    getch();
    return;
}

void menuRemover(Lista* li){
    imprimirMenu();
    printf("---------------- Remover Dados ----------------\n\n");

    if (listaVazia(li)){
        printf("Não há nada para excluir, pois a lista está vazia!\n\n");
        getch();
        return;
    }

    int codigo = lerInteiro("Digite o código de quem deseja remover: ", 0, MAX_INT);

    int x = remover(li, codigo);

    if (x == -1){
        printf("\nNão foi possível encontrar o usuário indicado!\n\n");
    } else {
        if (x == 0){
            printf("\nNão há nada para excluir, pois a lista está vazia!\n\n");
        } else {
            printf("\nDados removidos com sucesso!\n\n");
        }
    }

    getch();
    return;
}
