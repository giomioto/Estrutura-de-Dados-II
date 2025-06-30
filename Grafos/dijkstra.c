#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXVERTICES 100

enum {
    UMUARAMA = 0, CIANORTE, PARANAVAI, MARINGA, CAMPO_MOURAO,
    APUCARANA, LONDRINA, CORNELIO_PROCOPIO
};

char *nomes[] = {
    "UMUARAMA", "CIANORTE", "PARANAVAI", "MARINGA", "CAMPO MOURAO",
    "APUCARANA", "LONDRINA", "CORNELIO PROCOPIO"
};

void le_grafo_umuarama(int *custos) {
    for (int i = 0; i < MAXVERTICES * MAXVERTICES; i++)
        custos[i] = -1;
    custos[UMUARAMA * MAXVERTICES + CIANORTE] = custos[CIANORTE * MAXVERTICES + UMUARAMA] = 80;
    custos[UMUARAMA * MAXVERTICES + PARANAVAI] = custos[PARANAVAI * MAXVERTICES + UMUARAMA] = 140;
    custos[CIANORTE * MAXVERTICES + PARANAVAI] = custos[PARANAVAI * MAXVERTICES + CIANORTE] = 100;
    custos[CIANORTE * MAXVERTICES + MARINGA] = custos[MARINGA * MAXVERTICES + CIANORTE] = 75;
    custos[CIANORTE * MAXVERTICES + CAMPO_MOURAO] = custos[CAMPO_MOURAO * MAXVERTICES + CIANORTE] = 80;
    custos[PARANAVAI * MAXVERTICES + MARINGA] = custos[MARINGA * MAXVERTICES + PARANAVAI] = 70;
    custos[MARINGA * MAXVERTICES + CAMPO_MOURAO] = custos[CAMPO_MOURAO * MAXVERTICES + MARINGA] = 90;
    custos[MARINGA * MAXVERTICES + APUCARANA] = custos[APUCARANA * MAXVERTICES + MARINGA] = 60;
    custos[MARINGA * MAXVERTICES + LONDRINA] = custos[LONDRINA * MAXVERTICES + MARINGA] = 90;
    custos[APUCARANA * MAXVERTICES + LONDRINA] = custos[LONDRINA * MAXVERTICES + APUCARANA] = 50;
    custos[LONDRINA * MAXVERTICES + CORNELIO_PROCOPIO] = custos[CORNELIO_PROCOPIO * MAXVERTICES + LONDRINA] = 60;
}

void dijkstra(int vertices, int origem, int destino, int *custos, int use_names) {
    int i, v = -1;
    int ant[MAXVERTICES];
    int z[MAXVERTICES];
    double min;
    double dist[MAXVERTICES];

    for (i = 0; i < vertices; i++) {
        if (custos[(origem - 1) * MAXVERTICES + i] != -1) {
            ant[i] = origem - 1;
            dist[i] = custos[(origem - 1) * MAXVERTICES + i];
        } else {
            ant[i] = -1;
            dist[i] = HUGE_VAL;
        }
        z[i] = 0;
    }
    dist[origem - 1] = 0;
    z[origem - 1] = 1;
    do {
        min = HUGE_VAL;
        for (i = 0; i < vertices; i++) {
            if (!z[i] && dist[i] < min) {
                min = dist[i];
                v = i;
            }
        }
        if (min != HUGE_VAL && v != destino - 1) {
            z[v] = 1;
            for (i = 0; i < vertices; i++) {
                if (!z[i] && custos[v * MAXVERTICES + i] != -1) {
                    if (dist[v] + custos[v * MAXVERTICES + i] < dist[i]) {
                        dist[i] = dist[v] + custos[v * MAXVERTICES + i];
                        ant[i] = v;
                    }
                }
            }
        }
    } while (v != destino - 1 && min != HUGE_VAL);

    if (dist[destino - 1] == HUGE_VAL) {
        if (use_names) {
            printf("\nNao existe caminho entre %s e %s !!\n", nomes[origem - 1], nomes[destino - 1]);
        } else {
            printf("\nNao existe caminho entre o vertice %d e o vertice %d !!\n", origem, destino);
        }
    } else {
        if (use_names) {
            printf("\nMenor distancia de %s para %s encontrada!\n", nomes[origem - 1], nomes[destino - 1]);
        } else {
            printf("\nMenor distancia do vertice %d para o vertice %d encontrada!\n", origem, destino);
        }
        printf("Custo total: %d\n", (int)dist[destino - 1]);
        printf("Caminho (ordem reversa): ");
        i = destino - 1;
        while (i != -1) {
            if (use_names) {
                printf("%s", nomes[i]);
            } else {
                printf("V%d", i + 1);
            }
            i = ant[i];
            if (i != -1) {
                printf(" <- ");
            }
        }
        printf("\n");
    }
}

int main(void) {
    char opcao;
    int i, custo;
    int vertices = 0;
    int origem, destino;
    int *custos = NULL;

    do {
        system("cls");
        printf("\n======================================================\n");
        printf("     Calculadora de Rotas - Algoritmo de Dijkstra\n");
        printf("======================================================\n");
        printf("     1. Digitar um grafo manualmente\n");
        printf("     2. Calcular caminho minimo (grafo manual)\n");
        printf("     3. Carregar grafo de UMUARAMA\n");
        printf("     4. Listar municipios do grafo de Umuarama\n");
        printf("     5. Calcular caminho de UMUARAMA para outro municipio\n");
        printf("     6. Sair do programa\n\n");
        printf("Opcao: ");
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1':
                system("cls");
                do {
                    printf("\nNumero de vertices (entre 2 e %d): ", MAXVERTICES);
                    scanf("%d", &vertices);
                } while (vertices < 2 || vertices > MAXVERTICES);
                if(custos) free(custos);
                custos = (int *)malloc(sizeof(int) * MAXVERTICES * MAXVERTICES);
                for (i = 0; i < MAXVERTICES * MAXVERTICES; i++) custos[i] = -1;
                printf("Digite agora as arestas\n");
                do {
                    do {
                        printf("Origem da aresta (entre 1 e %d ou 0 para sair): ", vertices);
                        scanf("%d", &origem);
                    } while (origem < 0 || origem > vertices);
                    if (origem) {
                        do {
                            printf("Destino da aresta (entre 1 e %d, diferente de %d): ", vertices, origem);
                            scanf("%d", &destino);
                        } while (destino < 1 || destino > vertices || destino == origem);
                        do {
                            printf("Custo (positivo) da aresta de %d para %d: ", origem, destino);
                            scanf("%d", &custo);
                        } while (custo < 0);
                        custos[(origem - 1) * MAXVERTICES + (destino - 1)] = custo;
                    }
                } while (origem);
                printf("\nGrafo inserido!\n");
                system("pause");
                break;

            case '2':
                system("cls");
                if (!custos) {
                    printf("\nNenhum grafo manual carregado. Escolha a opcao 1 primeiro.\n");
                } else {
                    printf("\nCalculando caminho para o grafo manual de %d vertices.\n", vertices);
                    do {
                        printf("Vertice origem (entre 1 e %d): ", vertices);
                        scanf("%d", &origem);
                    } while (origem < 1 || origem > vertices);
                    do {
                        printf("Vertice destino (entre 1 e %d, diferente de %d): ", vertices, origem);
                        scanf("%d", &destino);
                    } while (destino < 1 || destino > vertices || destino == origem);
                    dijkstra(vertices, origem, destino, custos, 0);
                }
                system("pause");
                break;

            case '3':
                system("cls");
                vertices = 8;
                if(custos) free(custos);
                custos = (int *)malloc(sizeof(int) * MAXVERTICES * MAXVERTICES);
                le_grafo_umuarama(custos);
                printf("\nGrafo de UMUARAMA carregado com sucesso!\n");
                system("pause");
                break;

            case '4':
                system("cls");
                printf("\nPosicoes dos municipios (Indices do Grafo):\n");
                for(int j=0; j<8; j++){
                    printf("%d: %s\n", j, nomes[j]);
                }
                system("pause");
                break;

            case '5':
                system("cls");
                vertices = 8;
                if (!custos) {
                    custos = (int *)malloc(sizeof(int) * MAXVERTICES * MAXVERTICES);
                    le_grafo_umuarama(custos);
                    printf("\nGrafo de Umuarama carregado automaticamente.\n");
                }
                printf("\nEscolha a cidade destino a partir de UMUARAMA:\n");
                for (int j = 1; j < vertices; j++) {
                    printf("%d - %s\n", j, nomes[j]);
                }
                do {
                    printf("\nDestino (numero entre 1 e 7): ");
                    scanf("%d", &destino);
                } while (destino < 1 || destino > 7);
                dijkstra(vertices, UMUARAMA + 1, destino + 1, custos, 1);
                system("pause");
                break;

            case '6':
                system("cls");
                printf("\nSaindo do programa...\n");
                break;

            default:
                system("cls");
                printf("\nOpcao invalida. Tente novamente.\n");
                system("pause");
        }
    } while (opcao != '6');

    if (custos) {
        free(custos);
    }
    
    return 0;
}