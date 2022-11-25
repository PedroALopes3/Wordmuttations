#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Arestas.h"

struct arestas_lista
{
    Item this;
    arestas *next;
};



arestas * initarestas(void)
{
    return NULL;
}


//liberta vector de lista com as arestas para um nodo
void freearestas(arestas *first, void (* freeItemFnt)(Item))
{
    arestas *aux, *next;

    /* Cycle from the first to the last element           */
    for(aux = first; aux != NULL; aux = next)
    {
        next = aux->next;           /* Keep track of the next node */
        freeItemFnt(aux->this);     /* Free current item data with passed function */
        free(aux);                  /* Free current node    */
    }
    return;
}


// permite saber o comprimento da lista logo o numero de arestas
int lengtharestas(arestas *first)
{
    arestas *aux;
    int counter;

    /* Length determination cycle                                   */
    for(aux = first, counter = 0;
        aux!=NULL;
        counter++, aux = aux->next);

    return counter;
}

// Da return do proximo elemento da lista(aresta) 
arestas* getNextNodearestas(arestas * node)
{
  return ((node == NULL) ? NULL : node->next);
}


//Da return do conteudo da aresta
Item getItemarestas(arestas *node)
{
    if(node == NULL)  /* Check that node is not empty */
        return NULL;

    return node->this;
}



//insere aresta no grafo

arestas *insertUnsortedarestas(arestas *next, Item this)
{
    arestas *new;

    /* Memory allocation */
    new = (arestas *) malloc(sizeof(arestas));

    /* Check memory allocation errors */
    if(new == NULL)
        return NULL;

    /* Initialize new node */
    new->this = this;
    new->next = next;

    return new;
}


// funçao que compara as letras de 2 palavras
int N_mutacoes(char *palavra_1, char *palavra_2, int maximutacoes)
{
    int comprimento = strlen(palavra_1);
    int n_mutacoes = 0;
    for (int i = 0; (i < comprimento) && (n_mutacoes <= maximutacoes); i++)
    {
        if (palavra_1[i] != palavra_2[i])
        {
            n_mutacoes++;
        }
    }
    
    return n_mutacoes;

}

int N_mutacoes1 (char *palavra_1, char *palavra_2)
{
    int comprimento = strlen(palavra_1);
    int n_mutacoes = 0;
    for (int i = 0; (i < comprimento); i++)
    {

        if (palavra_1[i] != palavra_2[i])
        {
            n_mutacoes++;
        }
    }
    return n_mutacoes;
}