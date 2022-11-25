#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include "Dicionario.h"
#include "Dijkstra.h"

typedef struct _aresta
{
    int destino;
    int weight;
} _aresta;

void maior_mutacao(char *ficheiro, int *maiorMutacao)
{
    int funcionalidade, l = 0;
    FILE *Palavras;

    Palavras = fopen(ficheiro, "r");
    if (Palavras == NULL)
    {

        exit(0);
    }
    else
    {
        // buffer de leitura para as palavras
        char Palavra_1[100] = {'0'};
        char Palavra_2[100] = {'0'};

        // lê os problemas do ficheiro de entrada
        while (fscanf(Palavras, "%s %s %d", Palavra_1, Palavra_2, &funcionalidade) != EOF)
        {
            l = strlen(Palavra_1) - 1;
           
            if ((funcionalidade > maiorMutacao[l]) && (funcionalidade < l + 1))
            {
                maiorMutacao[l] = funcionalidade;
                
            }
        }
    }
    fclose(Palavras);
}

int main(int argc, char *argv[])
{

    // N - numero total de palavras no dicionario
    // foi removido pois nao era usado e dava warning: variable not used

    int n = 0, i = 0, comprimento = 0;
    char *ficheiro_saida;
    FILE *Dicionario = NULL;
    FILE *Palavras = NULL;
    FILE *Output = NULL;
    _aresta *pint1, *pint2;
    arestas ***Nodos;

    // Funcionalidade
    int Funcionalidade = 0;

    // verifica se sao passados os argumentos suficientes
    if (argc != 3)
    {
        return 0;
    }

    // verifica se os ficheiro de entrada tem o formato correto
    int vd = 0;
    int d = strlen(argv[1]);
    if (argv[1][d - 1] == 't')
    {
        vd++;
    }
    if (argv[1][d - 2] == 'c')
    {
        vd++;
    }
    if (argv[1][d - 3] == 'i')
    {
        vd++;
    }
    if (argv[1][d - 4] == 'd')
    {
        vd++;
    }
    if (argv[1][d - 5] == '.')
    {
        vd++;
    }

    int vp = 0;
    int p = strlen(argv[2]);
    if (argv[2][p - 1] == 's')
    {
        vp++;
    }
    if (argv[2][p - 2] == 'l')
    {
        vp++;
    }
    if (argv[2][p - 3] == 'a')
    {
        vp++;
    }
    if (argv[2][p - 4] == 'p')
    {
        vp++;
    }
    if (argv[2][p - 5] == '.')
    {
        vp++;
    }

    if ((vd != 5) || (vp != 5))
    {
        return 0;
    }

    // tamanho_palavra[i] indica o n de palavras com tamanho i
    int tamanho_palavras[100] = {0};

    // guarda a maior mutacao para cada tamanho de palavra
    int maiorMutacao[100] = {0};

    // Permite saber se ja foi criado o grafo para palavras de tamanho i;
    int existeGrafo[100] = {0};

    // Abre o ficheiro e conta o n de palavras
    Contagem_Npalavras(argv[1], Dicionario, tamanho_palavras);

    // Verifica qual a maior palavra no dicionario
    int tamanho_max_palavra = 0;
    for (i = 0; i < 100; i++)
    {
        if (tamanho_palavras[i] > 0)
        {
            tamanho_max_palavra = i + 1;
        }
    }

    // aloca tabelas para o dicionario relativos aos diferentes tamanhos de palavra
    char ***tabela_DIC = (char ***)malloc(tamanho_max_palavra * sizeof(char **));
    if (tabela_DIC == NULL)
    {
        return 0;
    }
    for (i = 0; i < tamanho_max_palavra; i++)
    {
        if (tamanho_palavras[i] > 0)
        {
            tabela_DIC[i] = (char **)malloc(tamanho_palavras[i] * sizeof(char *));
            if (tabela_DIC[i] == NULL)
            {
                return 0;
            }
        }
        else
        {
            tabela_DIC[i] = NULL;
        }
    }

    // Importa dicionario para as diferentes tabelas
    int e = Importacao_Dicionario(argv[1], Dicionario, tabela_DIC, tamanho_palavras);
    if (e == -1)
    {
        return 0;
    }

    // Ordena dicionario alfabeticamente
    for (i = 0; i < tamanho_max_palavra; i++)
    {
        if (tamanho_palavras[i] > 0)
        {
            quickSort(tabela_DIC, i, 0, tamanho_palavras[i] - 1);
        }
    }

    /*obtemos a maior mutacao presente no ficheiro de problemas para cada tamanho de palavra de forma a
          apenas fazermos vertices de tamanho maximo igual a maior mutacao                                    */
    maior_mutacao(argv[2], maiorMutacao);

    /* guarda a informacao sobre o numero de ligacoes de cada vertice */
    int **ligacoes = (int **)malloc(tamanho_max_palavra * sizeof(int *));
    if (ligacoes == NULL)
    {
        return 0;
    }
    for (int x = 0; x < tamanho_max_palavra; x++)
    {
        ligacoes[x] = (int *)malloc(tamanho_palavras[x] * sizeof(int));
        if (ligacoes[x] == NULL)
        {
            return 0;
        }
        for (int y = 0; y < tamanho_palavras[x]; y++)
        {
            ligacoes[x][y] = 0;
        }
    }

    // abre o ficheiro de entrada (problemas)
    Palavras = fopen(argv[2], "r");
    if (Palavras == NULL)
    {

        // Liberta a tabela que guarda o dicionario
        libertadicionario(tamanho_max_palavra, tamanho_palavras, tabela_DIC);
        return 0;
    }
    else
    {
        // determina o path para o ficheiro de saida
        int c = strlen(argv[2]);
        ficheiro_saida = (char *)malloc((c + 2) * sizeof(char));
        if (ficheiro_saida == NULL)
        {
            return 0;
        }
        strcpy(ficheiro_saida, argv[2]);
        ficheiro_saida[c + 1] = '\0';
        ficheiro_saida[c] = 's';
        ficheiro_saida[c - 1] = 'h';
        ficheiro_saida[c - 2] = 't';
        ficheiro_saida[c - 3] = 'a';
        ficheiro_saida[c - 4] = 'p';

        // aloca espaco para os diferentes grafos
        Nodos = (arestas ***)malloc(tamanho_max_palavra * sizeof(arestas **));
        if (Nodos == ((arestas ***)NULL))
        {
            return 0;
        }
        for (i = 0; i < tamanho_max_palavra; i++)
        {
            Nodos[i] = NULL;
        }

        // abre-se ficheiro de saida, calcula-se a solucao e impreme-se
        Output = fopen(ficheiro_saida, "w+");
        if (Output == NULL)
        {
            // Liberta a tabela que guarda o dicionario
            libertadicionario(tamanho_max_palavra, tamanho_palavras, tabela_DIC);
            return 0;
        }
        else
        {
            // guarda o indice das palavras no dicionario
            int i1, i2;

            // buffer de leitura para as palavras
            char Palavra_1[100] = {'0'};
            char Palavra_2[100] = {'0'};

            // vetor com informacao sobre a procura das palavras no dicionario (0:1)
            int check[2] = {0};

            // lê os problemas do ficheiro de entrada
            while (fscanf(Palavras, "%s %s %d", Palavra_1, Palavra_2, &Funcionalidade) != EOF)
            {

                comprimento = strlen(Palavra_1) - 1;
                int comprimento_1 = strlen(Palavra_2);
                n = tamanho_palavras[comprimento];
                check[0] = 0;
                check[1] = 0;
                
                int s = N_mutacoes1(Palavra_1, Palavra_2);

                // vetor com distancia minima aos restantes vertices na primeira fila e na segunda o vertice anterior
                int **distancias = (int **)malloc(2 * sizeof(int *));

                // casos impossiveis
                i1 = binarySearch(tabela_DIC, Palavra_1, comprimento, n);
                if (i1 == -1)
                {
                    check[0] = 1;
                }
                i2 = binarySearch(tabela_DIC, Palavra_2, comprimento, n);
                if (i2 == -1)
                {
                    check[1] = 1;
                }

                // problemas impossiveis:
                if (
                    (check[0] == 1)                      ||
                    (check[1] == 1)                      ||
                    ((comprimento + 1) != comprimento_1) ||
                    (comprimento > tamanho_max_palavra)  ||
                    (tamanho_palavras[comprimento] == 0) ||
                    (Funcionalidade < 0)                 ||
                    ((s == 1) && (Funcionalidade < 1))   ||
                    ((Funcionalidade == 0) && (s > 0))     )
                {
                    fprintf(Output, "%s -1\n", Palavra_1);
                    fprintf(Output, "%s\n", Palavra_2);
                    fprintf(Output, "\n");
                    continue;
                }

                // palavras com diferenca de 1
                else if ((1 == s) && (Funcionalidade >= 1))
                {
                    fprintf(Output, "%s 1\n", Palavra_1);
                    fprintf(Output, "%s\n", Palavra_2);
                    fprintf(Output, "\n");
                    continue;
                }

                // palavras iguais
                else if (Funcionalidade >= 0 && s == 0)
                {
                    fprintf(Output, "%s 0\n", Palavra_1);
                    fprintf(Output, "%s\n", Palavra_2);
                    fprintf(Output, "\n");
                    continue;
                }

                else if (existeGrafo[comprimento] == 1 && (Funcionalidade < comprimento + 1))
                {
                    // ja existe grafo daquele tamanho de palavra

                    distancias[0] = malloc(n * sizeof(int));
                    distancias[1] = malloc(n * sizeof(int));

                    dijkstra(Nodos[comprimento], i1, i2, n, distancias, Funcionalidade);

                    int dist = distancias[0][i2];

                    // imprime caminho para o ficheiro caso ele exista
                    if (dist != 1000000)
                    {
                        fprintf(Output, "%s %d\n", Palavra_1, dist);
                        impressora_recurvisa(distancias, tabela_DIC, comprimento, i1, i2, Output);
                        fprintf(Output, "\n");
                    }
                    else
                    {
                        fprintf(Output, "%s -1\n", Palavra_1);
                        fprintf(Output, "%s\n", Palavra_2);
                        fprintf(Output, "\n");
                    }

                    free(distancias[0]);
                    free(distancias[1]);
                    free(distancias);
                    continue;
                }

                // cria o grafo para o tamanho de palavra caso ele ainda nao tenha sido criado
                else if ((Funcionalidade < comprimento + 1) && (existeGrafo[comprimento] == 0))
                {
                    /* create vector for adjacency lists, one per node */
                    Nodos[comprimento] = (arestas **)malloc(n * sizeof(arestas *));
                    if (Nodos[comprimento] == NULL)
                    {
                        exit(0);
                    }
                    for (i = 0; i < tamanho_palavras[comprimento]; i++)
                    {
                        Nodos[comprimento][i] = NULL;
                    }
                    int peso;

                    /* read ne edges from file, each triple n1, n2, weight */
                    for (i = 0; i < n; i++)
                    {
                        for (int u = i + 1; u < n; u++)
                        {   // printf("%s %s %d",tabela_DIC[comprimento][i], tabela_DIC[comprimento][u],maiorMutacao[comprimento]);
                            peso = N_mutacoes(tabela_DIC[comprimento][i], tabela_DIC[comprimento][u], maiorMutacao[comprimento]);
                            // printf(" %d\n",peso);
                            if ((peso <= maiorMutacao[comprimento]) && (peso > 0))
                            {  
                                
                                ligacoes[comprimento][i]++;
                                ligacoes[comprimento][u]++;
                                pint1 = (_aresta *)malloc(sizeof(_aresta));
                                if (pint1 == ((_aresta *)NULL))
                                {
                                    exit(0);
                                }
                                pint2 = (_aresta *)malloc(sizeof(_aresta));
                                if (pint2 == ((_aresta *)NULL))
                                {
                                    exit(0);
                                }
                                pint1->destino = u;
                                pint1->weight = (peso * peso);
                                pint2->destino = i;
                                pint2->weight = (peso * peso);
                                if (Nodos[comprimento][u] == NULL)
                                {
                                    Nodos[comprimento][u] = initarestas();
                                }
                                if (Nodos[comprimento][i] == NULL)
                                {
                                    Nodos[comprimento][i] = initarestas();
                                }

                                Nodos[comprimento][u] = insertUnsortedarestas(Nodos[comprimento][u], pint2);
                                Nodos[comprimento][i] = insertUnsortedarestas(Nodos[comprimento][i], pint1);
                            }
                        }
                    }
                    for (int x = 0; x < tamanho_palavras[comprimento]; x++)
                    {
                        if (ligacoes[comprimento][x] == 0)
                        {
                            Nodos[comprimento][x] = NULL;
                        }
                    }
                    existeGrafo[comprimento] = 1;

                    // agora com o grafo ja construido executa
                    // o algoritmo de dijkstra

                    distancias[0] = malloc(n * sizeof(int));
                    distancias[1] = malloc(n * sizeof(int));

                    dijkstra(Nodos[comprimento], i1, i2, n, distancias, Funcionalidade);

                    int dist = distancias[0][i2];

                    // imprime caminho para o ficheiro caso ele exista
                    if (dist != 1000000)
                    {
                        fprintf(Output, "%s %d\n", Palavra_1, dist);

                        impressora_recurvisa(distancias, tabela_DIC, comprimento, i1, i2, Output);
                        fprintf(Output, "\n");
                    }
                    else
                    {
                        fprintf(Output, "%s -1\n", Palavra_1);
                        fprintf(Output, "%s\n", Palavra_2);
                        fprintf(Output, "\n");
                    }

                    free(distancias[0]);
                    free(distancias[1]);
                    free(distancias);
                    continue;
                }
                // caso o grafo seja muito denso
                else if (Funcionalidade >= comprimento + 1)
                {
                    // algoritmo de djikstra

                    distancias[0] = malloc(n * sizeof(int));
                    distancias[1] = malloc(n * sizeof(int));

                    dijkstra_muito_denso(tabela_DIC[comprimento], i1, i2, n, distancias, Funcionalidade);

                    int dist = distancias[0][i2];

                    // imprime caminho para o ficheiro caso ele exista
                    if (dist != 1000000)
                    {
                        fprintf(Output, "%s %d\n", Palavra_1, dist);

                        impressora_recurvisa(distancias, tabela_DIC, comprimento, i1, i2, Output);
                        fprintf(Output, "\n");
                    }
                    else
                    {
                        fprintf(Output, "%s -1\n", Palavra_1);
                        fprintf(Output, "%s\n", Palavra_2);
                        fprintf(Output, "\n");
                    }

                    free(distancias[0]);
                    free(distancias[1]);
                    free(distancias);
                    continue;
                }
            }
        }
        fclose(Output);
    }

    fclose(Palavras);

    free(ficheiro_saida);
    for (int x = 0; x < tamanho_max_palavra; x++)
    {
        free(ligacoes[x]);
    }
    free(ligacoes);

    // liberta os diversos grafos

    for (int y = 0; y < tamanho_max_palavra; y++)
    {
        if (existeGrafo[y] == 1)
        {
            for (i = 0; i < tamanho_palavras[y]; i++)
            {
                freearestas(Nodos[y][i], free);
            }
        }
        free(Nodos[y]);
    }

    free(Nodos);

    // Liberta a tabela que guarda o dicionario
    libertadicionario(tamanho_max_palavra, tamanho_palavras, tabela_DIC);
    return 0;
}
