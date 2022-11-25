#define DIST_INFINITA 1000000 // tamanho infinito de aresta
#include "Arestas.h"


struct MinHeapNode;
struct MinHeap;
typedef void *Item;

//

void dijkstra(arestas **grafo, int src,int chegada,int N_vertices,int** dist,int maiormutacao);
void swapMinHeapNode(struct MinHeapNode *a,struct MinHeapNode *b);
void minHeapify(struct MinHeap *minHeap, int idx);
struct MinHeapNode*  newMinHeapNode(int v,int dist);
struct MinHeap* createMinHeap(int capacity);
int isEmpty(struct MinHeap *minHeap);
struct MinHeapNode *extractMin(struct MinHeap *minHeap);
void decreaseKey(struct MinHeap* minHeap,int v, int dist);
bool isInMinHeap(struct MinHeap *minHeap, int v);
void impressora_recurvisa(int** dist,char*** tabela_Dic,int comprimento,int i1,int i,FILE* out);
void freeheap(struct MinHeap* pheap);
void dijkstra_muito_denso(char **tabela, int src, int chegada, int N_vertices, int **dist, int maiormutacao);

