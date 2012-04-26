/*
	Biblioteca de manipulacao de Grafos. Contém estruturas auxiliares para
	representacao e funcoes de leitura de manipulacao
	Autor: Marco Antonio Benatto
	Historico:
		* 22/09/2010 - Criacao das estruturas;
*/
#include "gstructs.h"

#define TRUE 1
#define FALSE 0
/*
	Tipo booleano
*/
typedef int BOOL;

/*
	Matriz de adjacencia e dados auxiliares para manipulacao
*/
typedef struct AdjMatrix{
	UINT **m;
	UINT last_i;
	UINT last_j;
}AdjMatrix;

/*
	Estrutura representando um grafo
*/
typedef struct Graph{
	AdjMatrix *am; /*Matriz de adjacencia*/
	Edge *e; /*Conjunto de arestas*/
	struct AdjList *al; /*Listas de adjacencia*/
	Vertice *v; /*Conjunto de vertices*/
	UINT sizev; /*Tamanho do conjunto de vertices*/
	UINT sizee; /*Tamanho do conjunto de arestas*/
	UINT last_epos; /*Ultima posicao ocupada do vetor de arestas*/
	UINT *in; /*O vetor chega para Busca em Profundidade*/
	UINT *out; /*O vetor sai para a Busca em Profundidade*/
	UINT count; /*Contador para a Busca em Profundidade*/
	void *slotinfo1; /*'Slot' de informacao (adiciona informacao extra ao grafo)*/
	void *slotinfo2; /*'Slot' de informacao (adiciona informacao extra ao grafo)*/
	void *slotinfo3; /*'Slot' de informacao (adiciona informacao extra ao grafo)*/
}Graph;

#ifdef GGDB
/*
	Buffer de impressao
		Utilizado para imprimir os resultados das buscas (emm caso de debug)
*/

typedef struct{
	char **eorder;
	int *vorder;
	int laste, lastv;
}PrintBuffer;
#endif

/*
	Nó de uma lista de adjacencia
*/
typedef struct AdjNode{
	UINT id;
	struct AdjNode *next;
	struct AdjNode *prev;
}AdjNode;

/*
	Lista de adjacência
*/
typedef struct AdjList{
	AdjNode *begin;
	AdjNode *end;
	UINT size;
}AdjList;

/*
	Forma de leitura do arquivo
*/
typedef enum ReadFlag{
	MTR_READ = 'M', /*Forma de leitura padrão - Matriz de adjacencia*/
	EDG_READ = 'L', /*Forma de leitura por arestas - a - b => e={a;b}*/
	PAR_READ = 'P' /*Forma de leitura por pares - a b => e={a;b}*/
}ReadFlag;

/*
	Descricao: Le dados de um arquivo
	Parametros: Caminho do arquivo,
				Modo de leitura
	Retorno: Estrutura de grafo
*/
Graph *ReadFile(char *path, ReadFlag rtype, int *n);

/*
	Descricao: Retorna a primeira aresta do grafo
	Parametros: Grafo
	Retorno: Aresta caso exista/null caso não haja nenhuma
*/
Edge *FirstEdge(Graph*);

/*
	Descricao: Retorna a proxima aresta do grafo
	Parametros: Grafo
	Retorno: Aresta caso exista/null caso não haja nenhuma
*/
Edge *NextEdge(Graph*);

/*
	Descricao: Insere aresta na lista de arestas
	Parametros: Grafo, u e v da aresta
*/
void InsertEdge(Graph *, int, int);

/*
	Descricao: Lista todas as arestas de G
	Parametros: Grafo
*/
void FindAllEdges(Graph *);

/*
	Descricao: Atualiza a lista de adjacencia de G
	Parametros: Grafo
*/
void UpdateAdjList(Graph *, int, int, BOOL);
