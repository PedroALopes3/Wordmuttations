//funcoes

int Contagem_Npalavras(char *ficheiro,FILE *Dicionario,int * tamanho_palavras);
int Importacao_Dicionario(char *ficheiro,FILE* Dicionario,char ***tabela_DIC,int* tamanho_palavras);
void swap(char *** tabela,int tamanho_palavras,int a,int b);
int partition(char ***Tabela,int tamanho_palavras, int minimo, int N_palavras);
void quickSort(char ***Tabela,int tamanho_palavras, int minimo, int N_palavras);
int binarySearch(char ***tabela_DIC, char *palavra, int tamanho_palavra, int N_palavras);
void libertadicionario (int tamanho_max_palavra, int* tamanho_palavras, char***tabela_DIC );
