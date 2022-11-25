#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "Dijkstra.h"
#include "Arestas.h"

typedef struct _aresta
{
    int destino;
    int weight;
} _aresta;

// Structure to represent a min heap node
struct MinHeapNode
{
    int v;
    int dist;
};

// Structure to represent a min heap
struct MinHeap
{

    // Number of heap nodes present currently
    int N_vertices;

    // Capacity of min heap
    int capacity;

    // This is needed for decreaseKey()
    int *pos;
    Item *array;
};

void dijkstra(arestas **grafo, int src, int chegada, int N_vertices, int **dist, int maiormutacao)
{

    // Get the number of vertices in graph
    int V = N_vertices;

    // minHeap represents set E
    struct MinHeap *minHeap = (struct MinHeap *)createMinHeap(V);

    // Initialize min heap with all
    // vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        dist[0][v] = DIST_INFINITA;
        dist[1][v] = DIST_INFINITA;
        minHeap->array[v] = newMinHeapNode(v, dist[0][v]);
        minHeap->pos[v] = v;
    }

    // Make dist value of src vertex
    // as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[0][src]);
    minHeap->pos[src] = src;
    dist[0][src] = 0;
    decreaseKey(minHeap, src, dist[0][src]);

    // Initially f of min heap is equal to V
    minHeap->N_vertices = V;

    // In the following loop,
    // min heap contains all nodes
    // whose shortest distance
    // is not yet finalized.

    while (isInMinHeap(minHeap, chegada) == true)
    {
        // Extract the vertex with
        // minimum distance value
        struct MinHeapNode *minHeapNode =
            extractMin(minHeap);

        // Store the extracted vertex number
        int u = minHeapNode->v;

        // Traverse through all adjacent
        // vertices of u (the extracted
        // vertex) and update
        // their distance values
        arestas *pCrawl = grafo[u];
        while (pCrawl != NULL)
        {
            _aresta *pint1 = getItemarestas((arestas *)pCrawl);
            int w = pint1->weight;

            if (w <= (maiormutacao * maiormutacao))
            {

                int v = pint1->destino;
                // If shortest distance to v is
                // not finalized yet, and distance to v
                // through u is less than its
                // previously calculated distance
                if (isInMinHeap(minHeap, v) &&
                    dist[0][u] != INT_MAX && pint1->weight + dist[0][u] < dist[0][v])
                {
                    dist[0][v] = dist[0][u] + pint1->weight;
                    dist[1][v] = u;

                    // update distance
                    // value in min heap also
                    decreaseKey(minHeap, v, dist[0][v]);
                }
            }
            pCrawl = getNextNodearestas(pCrawl);
        }
    }
    freeheap(minHeap);
    return;
}

// funcoes para trabalhar como o acervo

// A utility function to create a
// new Min Heap Node
struct MinHeapNode *newMinHeapNode(int v, int dist)
{
    struct MinHeapNode *minHeapNode = malloc(sizeof(struct MinHeapNode));
    if (minHeapNode == (struct MinHeapNode* ) NULL)
    {
        minHeapNode = NULL;
    }
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// A utility function to create a Min Heap
struct MinHeap *createMinHeap(int capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    if (minHeap == NULL)
    {
        minHeap = NULL;
    }
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    if (minHeap->pos == NULL)
    {
        minHeap->pos = NULL;
    }
    minHeap->N_vertices = 0;
    minHeap->capacity = capacity;
    minHeap->array = malloc(capacity * sizeof(struct MinHeapNode *));
    if (minHeap->array == NULL)
    {
        minHeap->array = NULL;
    }
    return minHeap;
}

// A utility function to swap two
// nodes of min heap.
// Needed for min heapify
void swapMinHeapNode(struct MinHeapNode *a, struct MinHeapNode *b)
{
    int v1, dist1;
    v1 = a->v;
    dist1 = a->dist;
    a->v = b->v;
    a->dist = b->dist;
    b->v = v1;
    b->dist = dist1;
}

// A standard function to
// heapify at given idx
// This function also updates
// position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap *minHeap,
                int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->N_vertices &&
        ((struct MinHeapNode *)(minHeap->array[left]))->dist <
            ((struct MinHeapNode *)(minHeap->array[smallest]))->dist)
        smallest = left;

    if (right < minHeap->N_vertices &&
        ((struct MinHeapNode *)(minHeap->array[right]))->dist <
            ((struct MinHeapNode *)(minHeap->array[smallest]))->dist)
        smallest = right;

    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        struct MinHeapNode *smallestNode =
            minHeap->array[smallest];
        struct MinHeapNode *idxNode =
            minHeap->array[idx];

        // Swap positions
        int a1 = smallestNode->v;
        int a2 = idxNode->v;
        minHeap->pos[a1] = idx;
        minHeap->pos[a2] = smallest;

        // Swap nodes
        swapMinHeapNode(minHeap->array[smallest],
                        minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// A utility function to check if
// the given minHeap is empty or not
int isEmpty(struct MinHeap *minHeap)
{
    return minHeap->N_vertices == 0;
}

// Standard function to extract
// minimum node from heap
struct MinHeapNode *extractMin(struct MinHeap *
                                   minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    // Store the root node
    struct MinHeapNode *root =
        minHeap->array[0];

    // Replace root node with last node
    struct MinHeapNode *lastNode =
        minHeap->array[minHeap->N_vertices - 1];
    minHeap->array[0] = lastNode;

    // Update position of last node
    minHeap->pos[root->v] = minHeap->N_vertices - 1;
    minHeap->pos[lastNode->v] = 0;

    // Reduce heap N_vertices and heapify root
    --minHeap->N_vertices;
    minHeapify(minHeap, 0);

    return root;
}

// Function to decreasekey dist value
// of a given vertex v. This function
// uses pos[] of min heap to get the
// current index of node in min heap
void decreaseKey(struct MinHeap *minHeap,
                 int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];

    // Get the node and updat<e its dist value
    ((struct MinHeapNode *)(minHeap->array[i]))->dist = dist;

    // Travel up while the complete
    // tree is not heapified.
    // This is a O(Logn) loop
    while (i && ((struct MinHeapNode *)(minHeap->array[i]))->dist <
                    ((struct MinHeapNode *)minHeap->array[(i - 1) / 2])->dist)
    {
        // Swap this node with its parent
        minHeap->pos[((struct MinHeapNode *)(minHeap->array[i]))->v] =
            (i - 1) / 2;
        minHeap->pos[((struct MinHeapNode *)minHeap->array[(i - 1) / 2])->v] = i;
        swapMinHeapNode(((struct MinHeapNode *)minHeap->array[i]),
                        ((struct MinHeapNode *)minHeap->array[(i - 1) / 2]));

        // move to parent index
        i = (i - 1) / 2;
    }
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->N_vertices)
        return true;
    return false;
}

// imprime o caminho

void impressora_recurvisa(int **dist, char ***tabela_Dic, int comprimento, int i1, int i, FILE *out)
{

    if (i != i1)
    {

        impressora_recurvisa(dist, tabela_Dic, comprimento, i1, dist[1][i], out);
        fprintf(out, "%s\n", tabela_Dic[comprimento][i]);
    }
}

void freeheap(struct MinHeap *pheap)
{
    struct MinHeapNode **iguais = malloc (pheap->capacity*sizeof(struct MinHeapNode *));
    if (iguais == NULL)
    {
        exit(0);
    }
    int index = 0, e = 0;
    for (int i = 0; i < (pheap->capacity); i++)
    {
        for (int x = 0; x < index; x++)
        {
            e = 0;
            if (pheap->array[i] == iguais[x])
            {   
                e = 1;
                break;
            }
        }
        if (e != 1)
        {
            iguais[index] = pheap->array[i];
            free(pheap->array[i]);
            index++;
        }
    }
    
    free(iguais);
    free(pheap->array);
    free(pheap->pos);
    free(pheap);
}

// dijkstra para problemas tal que o maximo de mutacoes e igual ou maior ao tamanho da palavra
void dijkstra_muito_denso(char **tabela, int src, int chegada, int N_vertices, int **dist, int maiormutacao)
{
    
    // Get the number of vertices in graph
    int V = N_vertices;

    // minHeap represents set E
    struct MinHeap *minHeap = (struct MinHeap *)createMinHeap(V);

    // Initialize min heap with all
    // vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        dist[0][v] = DIST_INFINITA;
        dist[1][v] = DIST_INFINITA;
        minHeap->array[v] = newMinHeapNode(v, dist[0][v]);
        minHeap->pos[v] = v;
    }

    // Make dist value of src vertex
    // as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[0][src]);
    minHeap->pos[src] = src;
    dist[0][src] = 0;
    decreaseKey(minHeap, src, dist[0][src]);

    // Initially f of min heap is equal to V
    minHeap->N_vertices = V;

    // In the following loop,
    // min heap contains all nodes
    // whose shortest distance
    // is not yet finalized.

    while (isInMinHeap(minHeap, chegada) == true)
    {
        // Extract the vertex with
        // minimum distance value
        struct MinHeapNode *minHeapNode =
            extractMin(minHeap);

        // Store the extracted vertex number
        int u = minHeapNode->v;

        // Traverse through all adjacent
        // vertices of u (the extracted
        // vertex) and update
        // their distance values
        for (int i = 0; i < N_vertices; i++)
        {
            if (i == u)
            {
                continue;
            }
            int w = N_mutacoes(tabela[u], tabela[i], maiormutacao);
            w = w*w;

            if (w <= (maiormutacao * maiormutacao))
            {

                int v = i;
                // If shortest distance to v is
                // not finalized yet, and distance to v
                // through u is less than its
                // previously calculated distance
                if (isInMinHeap(minHeap, v) &&
                    dist[0][u] != INT_MAX && w + dist[0][u] < dist[0][v])
                {
                    dist[0][v] = dist[0][u] + w;
                    dist[1][v] = u;

                    // update distance
                    // value in min heap also
                    decreaseKey(minHeap, v, dist[0][v]);
                }
            }
        }
    }
    freeheap(minHeap);
    return;
}
