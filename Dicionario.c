#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Dicionario.h"

char buffer[100] = {'0'};
int i = 0;

// Contabiliza o numero de palavras no dicionario
int N = 0;
int Contagem_Npalavras(char *ficheiro, FILE *Dicionario, int *tamanho_palavras)
{

    Dicionario = fopen(ficheiro, "r");
    if (Dicionario == NULL)
    {
        exit(0);
    }
    else
    {

        while (fscanf(Dicionario, "%s", buffer) == 1)
        {
            i = strlen(buffer);
            N++;
            if (i > 0)
            {
                tamanho_palavras[i - 1]++;
            }
        }
        fclose(Dicionario);
    }

    return N;
}

// Importacao do dicionario para uma tabela

int Importacao_Dicionario(char *ficheiro, FILE *Dicionario, char ***tabela_DIC, int *tamanho_palavras)
{
    // guarda os diferentes index ate onde cada tabela de tamanho i esta preenchida
    int index[100] = {0};

    Dicionario = fopen(ficheiro, "r");
    if (Dicionario == NULL)
    {
        return -1;
    }
    else
    {

        while (fscanf(Dicionario, "%s", buffer) != EOF)
        {
            i = strlen(buffer);
            tabela_DIC[i - 1][index[i - 1]] = (char *)malloc((i + 1) * sizeof(char));
            if (tabela_DIC[i - 1][index[i - 1]] == NULL)
            {
                return 0;
            }
            strcpy(tabela_DIC[i - 1][index[i - 1]], buffer);
            tabela_DIC[i - 1][index[i - 1]][i] = '\0';
            index[i - 1]++;
        }
        fclose(Dicionario);
    }
    return 1;
}

// A utility function to swap two elements
void swap(char ***tabela, int tamanho_palavras, int a, int b)
{
    if (a != b)
    {
        char buffer[100] = {'\0'};
        strcpy(buffer, tabela[tamanho_palavras][a]);
        strcpy(tabela[tamanho_palavras][a], tabela[tamanho_palavras][b]);
        strcpy(tabela[tamanho_palavras][b], buffer);
    }
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(char ***Tabela, int tamanho_palavras, int minimo, int N_palavras)
{
    char pivot[100] = {'\0'};
    strcpy(pivot, Tabela[tamanho_palavras][N_palavras]); // pivot
    int i = (minimo - 1);                                // Index of smaller element and indicates
                                                         // the right position of pivot found so far

    for (int j = minimo; j <= N_palavras - 1; j++)
    {
        // If current element is smaller than the pivot
        if (strcmp(Tabela[tamanho_palavras][j], pivot) < 0)
        {
            i++; // increment index of smaller element
            swap(Tabela, tamanho_palavras, i, j);
        }
    }
    swap(Tabela, tamanho_palavras, i + 1, N_palavras);
    return (i + 1);
}

void quickSort(char ***Tabela, int tamanho_palavras, int minimo, int N_palavras)
{
    if (minimo < N_palavras)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(Tabela, tamanho_palavras, minimo, N_palavras);

        // Separately sort elements before
        // partition and after partition
        quickSort(Tabela, tamanho_palavras, minimo, pi - 1);
        quickSort(Tabela, tamanho_palavras, pi + 1, N_palavras);
    }
}

int binarySearch(char ***tabela_DIC, char *palavra, int tamanho_palavra, int N_palavras)
{
    int min = 0;
    int max = N_palavras - 1;
    int meio = (min + max) / 2;
    while (min <= max)
    {
        meio = (min + max) / 2;

        if (strcmp(tabela_DIC[tamanho_palavra][meio], palavra) < 0)
        {
            min = meio + 1;
        }
        else if (strcmp(tabela_DIC[tamanho_palavra][meio], palavra) > 0)
        {
            max = meio - 1;
        }
        else
        {
            return meio;
        }
    }

    return -1;
}

// liberta a memoria alocada para a tabela de palavras
void libertadicionario(int tamanho_max_palavra, int *tamanho_palavras, char ***tabela_DIC)
{
    int i, n;

    for (i = 0; i < tamanho_max_palavra; i++)
    {
        for (n = 0; n < tamanho_palavras[i]; n++)
        {
            free(tabela_DIC[i][n]);
        }

        free(tabela_DIC[i]);
    }
    free(tabela_DIC);
}


