#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "graphlib.h"

Graph *ReadFile(char *path, ReadFlag rtype, int *n){
	Graph *g = (Graph*)malloc(sizeof(Graph));
	int i, size, u, v;
	FILE *in = fopen(path, "r");

	if (!in){
		fprintf(stderr, "Error on opening the source file...\n");
		exit(EBADF);
	}
	
	switch (rtype){
		case 'M':
			/*Numero de vertices do grafo*/
	    	*n = size = order_of_matrix(in);

			printf("Size...\n");

			/*Tamanho de v*/
			g->sizev = size;

			/*Aloca matriz de adjacencia*/
			g->am = (AdjMatrix*)malloc(sizeof(AdjMatrix));

			/*Aloca a matriz propriamente dita*/
			g->am->m = (UINT**)malloc(size * sizeof(UINT*));

			for (i = 0; i < size; i++)
				g->am->m[i] = (UINT*)malloc(size * sizeof(UINT));

			/*Ajeita os valores iniciais de i e j*/
			g->am->last_i = 0; /*Linha*/
			g->am->last_j = 1; /*Coluna*/
		
			/*Zera */
			g->last_epos = 0;		

			/*Aloca E*/
			g->e = (Edge*)malloc(size * size * sizeof(Edge));

			/*Aloca V*/
			g->v = (Vertice*)malloc(size * sizeof(Vertice));

			/*Insere os vertices*/
			for (i = 0; i < size; i++){
				g->v[i].id = i + 1;
				g->v[i].visited = 0;
			}
	
			/*le a matriz do arquivo pra dentro da matriz de adjacencia*/
			complete_matrix(path, g->am->m, size, size);
	
			/*Preenche todas as arestas*/
			FindAllEdges(g);
		break;
		case 'P':
			fscanf(stdin, "%d", n);
			
			g->v = (Vertice*)malloc((*n) * sizeof(Vertice));

			g->sizev = (*n);

			/*Adiciona os vertices*/
			for (i = 0; i < (*n); i++){
				g->v[i].id = i + 1;
				g->v[i].visited = 0;
			}

			/*Aloca E*/
			g->e = (Edge*)malloc((*n) * (*n) * sizeof(Edge));

			/*Aloca estrutura de matriz*/
			g->am = (AdjMatrix*)malloc(sizeof(AdjMatrix));

			/*Aloca a matriz*/
			g->am->m = (UINT**)calloc((*n), sizeof(UINT*));

			/*Aloca as linhas da matriz*/
			for (i = 0; i < (*n); i++)
				g->am->m[i] = (UINT*)calloc((*n),  sizeof(UINT));

			/*aloca os vetores de busca*/
			g->in = (UINT*)calloc((*n), sizeof(UINT));

			g->out = (UINT*)calloc((*n), sizeof(UINT));

			g->count = 0;

			/*le todas as arestas*/
			while (!feof(stdin) && fscanf(stdin, "%d %d", &u, &v) == 2)
				/*Insere as arestas*/
				InsertEdge(g, u, v);
			
		break;
		default:
			fprintf(stderr, "Undefined read format...closing...\n");
			exit(EINVAL);
		break;

	}

	return g;
}

Edge *FirstEdge(Graph *g){
	int i, j;

	for (i = g->am->last_i; i < g->sizev - 1; i++){
		for (j = g->am->last_j; i < g->sizev - 1; j++){
			if (g->am->m[i][j] == 1){
				Edge *e = (Edge*)malloc(sizeof(Edge));
				e->endpoint1 = i;
				e->endpoint2 = j;
				e->id = 1;

				return e;
			}
		}
	}

	return NULL;
}

void FindAllEdges(Graph *g){
	int i, j;
	UINT eid = 1;
	
	printf("|V(G)| = %d\n", g->sizev);

	for (i = 0; i <= g->sizev - 1; i++){
		for (j = i + 1; j <= g->sizev - 1; j++){
			if (g->am->m[i][j] == 1){
				g->e[g->last_epos].endpoint1 = i + 1;
				g->e[g->last_epos].endpoint2 = j + 1;			
				g->e[g->last_epos].id = eid;

				/*Atualiza lista de adjacencia*/
				UpdateAdjList(g, i + 1, j + 1, TRUE);
				g->sizee++;
				g->last_epos++;
				eid++;
			}
		}
	}
}


void InsertEdge(Graph *g, int u, int v){
	static int i = 1;
	g->e[g->last_epos].endpoint1 = u;
	g->e[g->last_epos].endpoint2 = v;
	g->e[g->last_epos].id = i;

	g->am->m[u - 1][v - 1] = 1;

	i++;
	g->last_epos++;
	g->sizee++;
}

/*Insere em l[u] o vertice v*/
void UpdateAdjList(Graph *g, int u, int v, BOOL sim){
	AdjNode *n = (AdjNode*)malloc(sizeof(AdjNode));

	if (!n){
		fprintf(stderr, "Error on creating a new AdjNode...\n");
		exit(ENOMEM);
	}

	/*Se a lista nao existir ainda, cria ela*/
	if (!g->al){
		int i = 0;
		g->al = (AdjList*)malloc(g->sizev * sizeof(AdjList));

		/*Limpa todos os elementos para garantir seguranca*/
		for (i = 0; i < g->sizev; i++){
			g->al[i].begin = g->al[i].end = NULL;
			g->al[i].size = 0;
		}
	}

	if (g->al[u - 1].size == 0){
		n->id = v;

		n->prev = n->next = NULL;

		g->al[u - 1].begin = g->al[u - 1].end = n;
		
		g->al[u - 1].size++;
	}else{
		n->id = v;
		
		/*Inserindo n na lista*/
		n->prev = g->al[u - 1].end;
		g->al[u - 1].end->next = n;
		g->al[u - 1].end = n;

		g->al[u - 1].size++;
	}

	if (sim == TRUE)
		UpdateAdjList(g, v, u, FALSE);
}
