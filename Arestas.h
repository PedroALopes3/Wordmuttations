typedef void *Item;

typedef struct arestas_lista arestas ;

arestas * initarestas(void);
void freearestas(arestas *first, void (* freeItemFnt)(Item));
int lengtharestas(arestas *first);
arestas* getNextNodearestas(arestas * node);
Item getItemarestas(arestas *node);
arestas *insertUnsortedarestas(arestas *next, Item this);
int N_mutacoes(char *palavra_1, char *palavra_2,int maximutacoes);
int N_mutacoes1(char *palavra_1, char *palavra_2);