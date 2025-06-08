/**********************************************************
 *                                                        *
 *        ██    ██ ███████ ███████ ██████  ██████         *
 *        ██    ██   ██    ██      ██   ██ ██   ██        *
 *        ██    ██   ██    █████   ██████  ██████         *
 *        ██    ██   ██    ██      ██      ██   ██        *
 *         ██████    ██    ██      ██      ██   ██        *
 *                                                        *
 *        Estudante: Giovanni Mioto - RA: 2603454         *
 *        Exercício 2 - ED2: Tabela Hash                  *
 *                                                        *
 **********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 8

struct hash
{
    char *palavra;
    char livre;
};

void inserir(struct hash *tabela, int pos, const char *palavra);
void consultar(struct hash *tabela, const char *palavra);
void exibir(struct hash *tabela);
void excluir(struct hash *tabela, const char *palavra);
void consultarLetra(struct hash *tabela, char letra);

void consultarLetra(struct hash *tabela, char letra)
{
    printf("\nPalavras que contem a letra '%c':\n", letra);
    for (int i = 0; i < TAM; i++)
    {
        if (tabela[i].livre == 'O' && tabela[i].palavra != NULL)
        {
            if (strchr(tabela[i].palavra, letra) != NULL)
            {
                printf("Posicao %d: %s\n", i, tabela[i].palavra);
            }
        }
    }
    getchar();
}

void consultar(struct hash *tabela, const char *palavra)
{
    int i = 0;
    int pos = palavra[0] % TAM;
    int indice;

    while (i < TAM)
    {
        indice = (pos + i) % TAM;

        if (tabela[indice].livre == 'O' && tabela[indice].palavra != NULL)
        {
            if (strcmp(tabela[indice].palavra, palavra) == 0)
            {
                printf("\nPalavra '%s' encontrada na posicao %d.\n", palavra, indice);
                return;
            }
        }
        else if (tabela[indice].livre == 'L')
        {
            break;
        }
        i++;
    }
    printf("\nPalavra '%s' nao encontrada.\n", palavra);
}


void exibir(struct hash *tabela)
{
    printf("\nPalavras na tabela hash:\n");
    for (int i = 0; i < TAM; i++)
    {
        if (tabela[i].livre == 'O' && tabela[i].palavra != NULL)
        {
            printf("Posicao %d: %s\n", i, tabela[i].palavra);
        }
        else
        {
            printf("Posicao %d: Livre\n", i);
        }
    }
}

void excluir(struct hash *tabela, const char *palavra)
{
    int i = 0;
    int pos = palavra[0] % TAM;
    int indice;

    while (i < TAM)
    {
        indice = (pos + i) % TAM;

        if (tabela[indice].livre == 'O' && tabela[indice].palavra != NULL)
        {
            if (strcmp(tabela[indice].palavra, palavra) == 0)
            {
                free(tabela[indice].palavra);
                tabela[indice].palavra = NULL;
                tabela[indice].livre = 'L';
                printf("\nPalavra '%s' excluida da posicao %d.\n", palavra, indice);
                return;
            }
        }
        else if (tabela[indice].livre == 'L')
        {
            break;
        }
        i++;
    }
    printf("\nPalavra '%s' nao encontrada para exclusao.\n", palavra);
}


void inserir(struct hash *tabela, int pos, const char *palavra)
{
    int i = 0;
    int indice;

    while (i < TAM)
    {
        indice = (pos + i) % TAM;
        if (tabela[indice].livre != 'O')
        {
            tabela[indice].palavra = malloc(strlen(palavra) + 1);
            if (tabela[indice].palavra == NULL)
            {
                printf("\nErro ao alocar memoria!\n");
                return;
            }
            strcpy(tabela[indice].palavra, palavra);
            tabela[indice].livre = 'O';
            return;
        }
        i++;
    }

    printf("\nTabela Cheia! Nao foi possivel inserir '%s'.\n", palavra);
}

int main()
{
    int opcao;
    char palavra[100];
    char letra;
    struct hash tabela[TAM];

    for (int i = 0; i < TAM; i++)
    {
        tabela[i].palavra = NULL;
        tabela[i].livre = 'L';
    }

    do
    {
        system("cls");
        printf("\nMenu:\n");
        printf("1. Inserir uma palavra\n");
        printf("2. Consultar uma palavra\n");
        printf("3. Exibir todas as palavras\n");
        printf("4. Exibir palavras com a letra escolhida\n");
        printf("5. Excluir uma palavra\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        fflush(stdin);

        system("cls");

        switch (opcao)
        {
        case 1:
            printf("Entre com uma palavra: ");
            scanf("%s", palavra);
            fflush(stdin);
            inserir(tabela, palavra[0] % TAM, palavra);
            break;
        case 2:
            printf("Entre com uma palavra para consultar: ");
            scanf("%s", palavra);
            fflush(stdin);
            consultar(tabela, palavra);
            break;
        case 3:
            exibir(tabela);
            break;
        case 4:
            printf("Entre com uma letra: ");
            scanf(" %c", &letra);
            consultarLetra(tabela, letra);
            break;
        case 5:
            printf("Entre com uma palavra para excluir: ");
            scanf("%s", palavra);
            fflush(stdin);
            excluir(tabela, palavra);
            break;
        case 6:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }

        if (opcao != 6)
        {
            printf("\nPressione Enter para continuar...");
            getchar();
        }

    } while (opcao != 6);

    for (int i = 0; i < TAM; i++)
    {
        if (tabela[i].palavra != NULL)
        {
            free(tabela[i].palavra);
        }
    }

    return 0;
}
