#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 10

// Estrutura que representa um componente necessário para a montagem da torre de fuga.

typedef struct
{
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Vetor que armazena os componentes.

Componente componentes[MAX_COMPONENTES];

// Quantidade atual de componentes cadastrados.

int quantidade = 0;

// Contador utilizado pelos algoritmos.

long comparacoes = 0;

// Indica se o vetor está ordenado por nome. Necessário para liberar a busca binária.

int ordenadoPorNome = 0;
void exibirMenu();

void cadastrarComponente();

void mostrarComponentes(
    Componente vetor[],
    int tamanho);

void bubbleSortNome(
    Componente vetor[],
    int tamanho);

void insertionSortTipo(
    Componente vetor[],
    int tamanho);

void selectionSortPrioridade(
    Componente vetor[],
    int tamanho);

int buscaBinariaPorNome(
    Componente vetor[],
    int tamanho,
    char nome[]);

double medirTempo(
    void (*algoritmo)(Componente[], int),
    Componente vetor[],
    int tamanho);

int main()
{
    int opcao;
    int posicao;
    char nomeBusca[30];
    double tempo;

    do
    {
        exibirMenu();

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            cadastrarComponente();
            break;

        case 2:
            mostrarComponentes(componentes, quantidade);
            break;

        case 3:
            tempo = medirTempo(
                bubbleSortNome,
                componentes,
                quantidade);

            printf("\nBubble Sort executado!\n");
            printf("Comparacoes: %ld\n", comparacoes);
            printf("Tempo: %.8lf segundos\n", tempo);

            mostrarComponentes(componentes, quantidade);
            break;

        case 4:
            tempo = medirTempo(
                insertionSortTipo,
                componentes,
                quantidade);

            printf("\nInsertion Sort executado!\n");
            printf("Comparacoes: %ld\n", comparacoes);
            printf("Tempo: %.8lf segundos\n", tempo);

            mostrarComponentes(componentes, quantidade);
            break;

        case 5:
            tempo = medirTempo(
                selectionSortPrioridade,
                componentes, quantidade);

            printf("\nSelection Sort executado!\n");
            printf("Comparacoes: %ld\n", comparacoes);
            printf("Tempo: %.8lf segundos\n", tempo);

            mostrarComponentes(componentes, quantidade);
            break;

        case 6:

            if (!ordenadoPorNome)
            {
                printf("\nPrimeiro ordene os componentes por nome (Opcao 3).\n");
                break;
            }

            printf("\nDigite o nome do componente-chave: ");
            fgets(nomeBusca, 30, stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

            posicao = buscaBinariaPorNome(
                componentes,
                quantidade,
                nomeBusca);

            if (posicao != -1)
            {
                printf("\nComponente encontrado!\n");

                printf("Nome: %s\n",
                       componentes[posicao].nome);

                printf("Tipo: %s\n",
                       componentes[posicao].tipo);

                printf("Prioridade: %d\n",
                       componentes[posicao].prioridade);

                printf("Comparacoes: %ld\n",
                       comparacoes);
            }
            else
            {
                printf("\nComponente nao encontrado.\n");
            }

            break;

        case 0:
            printf("\nEncerrando sistema...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
void exibirMenu()
{

    printf("\n========================================\n");
    printf(" FREE FIRE - TORRE DE RESGATE (NIVEL MESTRE)\n");
    printf("========================================\n");
    printf(" Mochila: %d/%d componentes \n", quantidade, MAX_COMPONENTES);

    printf("1 - Cadastrar componente\n");
    printf("2 - Listar componentes\n");

    printf("\n--- ORDENACAO ---\n");

    printf("3 - Ordenar Por Nome (Nome)\n");
    printf("4 - Ordenar Por Tipo (Tipo)\n");
    printf("5 - Ordenar Por Prioridade (Prioridade)\n");

    printf("\n--- BUSCA ---\n");

    printf("6 - Buscar componente-chave\n");

    printf("\n0 - ATIVACAO DA TORRE DE FUGA (Sair)\n");
}
// Cadastra um novo componente da torre.

void cadastrarComponente()
{

    if (quantidade >= MAX_COMPONENTES)
    {

        printf("\nLimite atingido.\n");
        return;
    }

    printf("\nNome: ");

    fgets(componentes[quantidade].nome,
          30,
          stdin);

    componentes[quantidade].nome[strcspn(
        componentes[quantidade].nome,
        "\n")] = '\0';

    printf("Tipo: ");

    fgets(componentes[quantidade].tipo, 20, stdin);

    componentes[quantidade].tipo[strcspn(
        componentes[quantidade].tipo,
        "\n")] = '\0';

    do
    {
        printf("Prioridade (1-10): ");
        scanf("%d", &componentes[quantidade].prioridade);
        getchar();

        if (componentes[quantidade].prioridade < 1 ||
            componentes[quantidade].prioridade > 10)
        {
            printf("Valor invalido! Digite entre 1 e 10.\n");
        }

    } while (componentes[quantidade].prioridade < 1 ||
             componentes[quantidade].prioridade > 10);

    quantidade++;

    ordenadoPorNome = 0;

    printf("\nComponente cadastrado com sucesso!\n");
}
// Mostra todos os componentes.

void mostrarComponentes(
    Componente vetor[],
    int tamanho)
{

    if (tamanho == 0)
    {

        printf("\nNenhum componente cadastrado.\n");
        return;
    }

    printf("\n====================================================\n");
    printf("%-25s %-15s %-10s\n",
           "NOME",
           "TIPO",
           "PRIORIDADE");

    printf("====================================================\n");

    for (int i = 0; i < tamanho; i++)
    {

        printf("%-25s %-15s %-10d\n",
               vetor[i].nome,
               vetor[i].tipo,
               vetor[i].prioridade);
    }
} /*
     Ordena os componentes pelo nome.
 */
void bubbleSortNome(
    Componente vetor[],
    int tamanho)
{

    comparacoes = 0;

    Componente temp;

    for (int i = 0; i < tamanho - 1; i++)
    {

        for (int j = 0;
             j < tamanho - i - 1;
             j++)
        {

            comparacoes++;

            if (strcmp(vetor[j].nome,
                       vetor[j + 1].nome) > 0)
            {

                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }

    ordenadoPorNome = 1;
}
// Ordena os componentes pelo tipo.

void insertionSortTipo(
    Componente vetor[],
    int tamanho)
{

    comparacoes = 0;

    for (int i = 1; i < tamanho; i++)
    {

        Componente chave = vetor[i];

        int j = i - 1;

        while (j >= 0)
        {
            comparacoes++;

            if (strcmp(vetor[j].tipo,
                       chave.tipo) <= 0)
            {
                break;
            }

            vetor[j + 1] = vetor[j];
            j--;
        }

        vetor[j + 1] = chave;
    }

    ordenadoPorNome = 0;
}
//   Ordena os componentes pela prioridade.

void selectionSortPrioridade(
    Componente vetor[],
    int tamanho)
{

    comparacoes = 0;

    for (int i = 0; i < tamanho - 1; i++)
    {

        int menor = i;

        for (int j = i + 1;
             j < tamanho;
             j++)
        {

            comparacoes++;

            if (vetor[j].prioridade <
                vetor[menor].prioridade)
            {

                menor = j;
            }
        }

        Componente temp = vetor[i];

        vetor[i] = vetor[menor];

        vetor[menor] = temp;
    }

    ordenadoPorNome = 0;
}

//  Busca um componente pelo nome.

int buscaBinariaPorNome(
    Componente vetor[],
    int tamanho,
    char nome[])
{

    int inicio = 0;
    int fim = tamanho - 1;

    comparacoes = 0;

    while (inicio <= fim)
    {

        int meio =
            (inicio + fim) / 2;

        comparacoes++;

        int resultado =
            strcmp(vetor[meio].nome,
                   nome);

        if (resultado == 0)
            return meio;

        if (resultado < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

// Mede o tempo de execução de qualquer algoritmo.

double medirTempo(
    void (*algoritmo)(Componente[], int),
    Componente vetor[],
    int tamanho)
{

    clock_t inicio, fim;

    inicio = clock();

    algoritmo(vetor, tamanho);

    fim = clock();

    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}
