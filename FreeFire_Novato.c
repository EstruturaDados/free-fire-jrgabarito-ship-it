#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Estrutura que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor para armazenar os itens
Item mochila[MAX_ITENS];

// Controla a quantidade atual de itens
int numItens = 0;

// Protótipos das funções
void inserirItem();
void removerItem();
void listarItens();
void exibirMenu();

int main() {

    int opcao;

    do {
        exibirMenu();

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o ENTER

        switch(opcao) {

            case 1:
                inserirItem();
                break;

            case 2:
                removerItem();
                break;

            case 3:
                listarItens();
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}

// Exibe o menu principal
void exibirMenu() {

    printf("\n=================================\n");
    printf("   FREE FIRE - MOCHILA LOOT\n");
    printf("=================================\n");
    printf("1 - Adicionar Item\n");
    printf("2 - Remover Item\n");
    printf("3 - Listar Itens\n");
    printf("0 - Sair\n");
    printf("=================================\n");
}

// Adiciona um novo item
void inserirItem() {

    if(numItens >= MAX_ITENS) {
        printf("\nMochila cheia! Limite de 10 itens.\n");
        return;
    }

    printf("\nNome do item: ");
    fgets(mochila[numItens].nome, 30, stdin);
    mochila[numItens].nome[strcspn(mochila[numItens].nome, "\n")] = '\0';

    printf("Tipo do item: ");
    fgets(mochila[numItens].tipo, 20, stdin);
    mochila[numItens].tipo[strcspn(mochila[numItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[numItens].quantidade);
    getchar();

    numItens++;

    printf("\nItem adicionado com sucesso!\n");
}

// Remove um item pelo nome
void removerItem() {

    char nomeBusca[30];
    int posicao = -1;

    if(numItens == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\nDigite o nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for(int i = 0; i < numItens; i++) {

        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
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

    printf("\nItem removido com sucesso!\n");
}

// Lista todos os itens cadastrados
void listarItens() {

    if(numItens == 0) {
        printf("\nNenhum item cadastrado.\n");
        return;
    }

    printf("\n================================================\n");
    printf("%-20s %-15s %-10s\n",
           "NOME", "TIPO", "QUANTIDADE");
    printf("================================================\n");

    for(int i = 0; i < numItens; i++) {

        printf("%-20s %-15s %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}