#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// =========================
// ESTRUTURAS
// =========================

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// =========================
// VARIAVEIS GLOBAIS
// =========================

// Vetor
Item mochila[MAX_ITENS];
int numItens = 0;

// Lista Encadeada
No *inicioLista = NULL;

// Contadores
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// =========================
// PROTOTIPOS MOCHILA
// =========================

void inserirItemMochila();
void removerItemMochila();
void listarItensMochila();
int buscarSequencialMochila(char nome[]);
void ordenarMochila();
int buscarBinariaMochila(char nome[]);

// =========================
// PROTOTIPOS LISTA
// =========================

void inserirItemLista();
void removerItemLista();
void listarItensLista();
No* buscarItemLista(char nome[]);

// =========================
// MENU
// =========================

void exibirMenu() {

    printf("\n=========================================\n");
    printf(" FREE FIRE - MOCHILA AVENTUREIRO\n");
    printf("=========================================\n");
    printf("\n=== MOCHILA (VETOR) ===\n");
    printf("1  - Inserir itens\n");
    printf("2  - Remover itens\n");
    printf("3  - Listar itens\n");
    printf("4  - Buscar itens (Sequencial)\n");
    printf("5  - Ordenar Mochila\n");
    printf("6  - Buscar itens (Binaria)\n");
    printf("\n");
    printf("\n=== MOCHILA DINAMICA (LISTA ENCADEADA) ===\n");
    printf("7  - Inserir itens\n");
    printf("8  - Remover itens\n");
    printf("9  - Listar itens\n");
    printf("10 - Buscar itens\n");
    printf("\n");
    printf("\n0  - Sair\n");
    printf("=========================================\n");
}

// =========================
// MAIN
// =========================

int main() {

    int opcao;
    char nomeBusca[30];
    int posicao;
    No *resultado;

    do {

        exibirMenu();

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {

            case 1:
                inserirItemMochila();
                break;

            case 2:
                removerItemMochila();
                break;

            case 3:
                listarItensMochila();
                break;

            case 4:

                printf("\nNome do item: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                posicao = buscarSequencialMochila(nomeBusca);

                if(posicao != -1) {

                    printf("\nItem encontrado!\n");
                    printf("Nome: %s\n", mochila[posicao].nome);
                    printf("Tipo: %s\n", mochila[posicao].tipo);
                    printf("Quantidade: %d\n",
                           mochila[posicao].quantidade);
                }
                else {
                    printf("\nItem nao encontrado.\n");
                }

                printf("Comparacoes: %d\n",
                       comparacoesSequencial);

                break;

            case 5:
                ordenarMochila();
                break;

            case 6:

                printf("\nATENCAO: Ordene o vetor antes!\n");

                printf("Nome do item: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                posicao = buscarBinariaMochila(nomeBusca);

                if(posicao != -1) {

                    printf("\nItem encontrado!\n");
                    printf("Nome: %s\n", mochila[posicao].nome);
                    printf("Tipo: %s\n", mochila[posicao].tipo);
                    printf("Quantidade: %d\n",
                           mochila[posicao].quantidade);
                }
                else {
                    printf("\nItem nao encontrado.\n");
                }

                printf("Comparacoes: %d\n",
                       comparacoesBinaria);

                break;

            case 7:
                inserirItemLista();
                break;

            case 8:
                removerItemLista();
                break;

            case 9:
                listarItensLista();
                break;

            case 10:

                printf("\nNome do item: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                resultado = buscarItemLista(nomeBusca);

                if(resultado != NULL) {

                    printf("\nItem encontrado!\n");
                    printf("Nome: %s\n",
                           resultado->dados.nome);
                    printf("Tipo: %s\n",
                           resultado->dados.tipo);
                    printf("Quantidade: %d\n",
                           resultado->dados.quantidade);
                }
                else {
                    printf("\nItem nao encontrado.\n");
                }

                printf("Comparacoes: %d\n",
                       comparacoesSequencial);

                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}

// =========================
// FUNCOES DA MOCHILA
// =========================

void inserirItemMochila() {

    if(numItens >= MAX_ITENS) {

        printf("\nMochila cheia!\n");
        return;
    }

    printf("\nNome: ");
    fgets(mochila[numItens].nome, 30, stdin);
    mochila[numItens].nome[
        strcspn(mochila[numItens].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(mochila[numItens].tipo, 20, stdin);
    mochila[numItens].tipo[
        strcspn(mochila[numItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[numItens].quantidade);
    getchar();

    numItens++;

    printf("\nItem inserido na Mochila (Vetor) com sucesso!\n");
}

void removerItemMochila() {

    char nome[30];
    int posicao = -1;

    if(numItens == 0) {

        printf("\nMochila vazia.\n");
        return;
    }

    printf("\nNome do item: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for(int i = 0; i < numItens; i++) {

        if(strcmp(mochila[i].nome, nome) == 0) {

            posicao = i;
            break;
        }
    }

    if(posicao == -1) {

        printf("\nItem nao encontrado.\n");
        return;
    }

    for(int i = posicao; i < numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    numItens--;

    printf("\nItem removido da Mochila (Vetor)!\n");
}

void listarItensMochila() {

    if(numItens == 0) {

        printf("\nMochila vazia.\n");
        return;
    }

    printf("\n===== ITENS DA MOCHILA (VETOR) =====\n");

    for(int i = 0; i < numItens; i++) {

        printf("\nNome: %s", mochila[i].nome);
        printf("\nTipo: %s", mochila[i].tipo);
        printf("\nQuantidade: %d\n",
               mochila[i].quantidade);
    }
}

int buscarSequencialMochila(char nome[]) {

    comparacoesSequencial = 0;

    for(int i = 0; i < numItens; i++) {

        comparacoesSequencial++;

        if(strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }

    return -1;
}

void ordenarMochila() {

    Item temp;

    for(int i = 0; i < numItens - 1; i++) {

        for(int j = 0; j < numItens - i - 1; j++) {

            if(strcmp(mochila[j].nome,
                      mochila[j + 1].nome) > 0) {

                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }

    printf("\nMochila ordenada com sucesso!\n");
}

int buscarBinariaMochila(char nome[]) {

    int inicio = 0;
    int fim = numItens - 1;

    comparacoesBinaria = 0;

    while(inicio <= fim) {

        int meio = (inicio + fim) / 2;

        comparacoesBinaria++;

        int resultado =
            strcmp(mochila[meio].nome, nome);

        if(resultado == 0)
            return meio;

        if(resultado < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

// =========================
// FUNCOES DA LISTA
// =========================

void inserirItemLista() {

    No *novo = (No*) malloc(sizeof(No));

    if(novo == NULL) {

        printf("\nErro de memoria.\n");
        return;
    }

    printf("\nNome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[
        strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[
        strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = inicioLista;
    inicioLista = novo;

    printf("\nItem inserido na Mochila Dinamica (Lista Encadeada)!\n");
}

void removerItemLista() {

    if(inicioLista == NULL) {
        printf("\nA Mochila Dinamica esta vazia.\n");
        return;
    }

    char nome[30];

    No *atual = inicioLista;
    No *anterior = NULL;

    printf("\nNome do item: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    while(atual != NULL &&
          strcmp(atual->dados.nome, nome) != 0) {

        anterior = atual;
        atual = atual->proximo;
    }

    if(atual == NULL) {

        printf("\nItem nao encontrado.\n");
        return;
    }

    if(anterior == NULL)
        inicioLista = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);

    printf("\nItem removido da Mochila Dinamica!\n");
}

void listarItensLista() {

    No *atual = inicioLista;

    if(atual == NULL) {

        printf("\nLista vazia.\n");
        return;
    }

    printf("\n===== ITENS DA MOCHILA DINAMICA =====\n");

    while(atual != NULL) {

        printf("\nNome: %s",
               atual->dados.nome);

        printf("\nTipo: %s",
               atual->dados.tipo);

        printf("\nQuantidade: %d\n",
               atual->dados.quantidade);

        atual = atual->proximo;
    }
}

No* buscarItemLista(char nome[]) {

    No *atual = inicioLista;

    comparacoesSequencial = 0;

    while(atual != NULL) {

        comparacoesSequencial++;

        if(strcmp(atual->dados.nome, nome) == 0) {
            return atual;
        }

        atual = atual->proximo;
    }

    return NULL;
}