#include "drawing_core.h"

#ifdef deprec
#include "drawing_core.h"


int min(int x, int y){
	return x > y ? y : x;
}

int max(int x, int y){
	return x > y ? x : y;
}

float VectorSize(int x, int y){
	return sqrt(x*x + y*y);
}

/*TODO: Posicionar os vertices de forma 'circular' em discos concentricos*/
/*Ideia:
	O primeiro vertice do vetor é posicionado na origem da circunferencia,
	os seus vizinhos no raio mais externo apartir da origem
*/
void InitialLayout(Vertice* v, int l, UINT **m){
	int i;
	queue *q;
	UINT vid, np, ns;
	int *visited = (int*)calloc(l, sizeof(int));
	float diff = 360/l;
	
	/*Inicializa o nivel pai e o nivel filho*/
	np = ns = 0;

	/*Vertice inicial na origem da circunferencia*/
	vid = v[0].id;
	v[0].x = 0;
	v[0].y = 0;
	v[0].depth = np;
	
	/*Incrementa nivel do filho*/
	ns++;

	/*Buscar em largura para posicionar todos os outros vertices*/
	fprintf(stdout, "Creating queue...\n");
	
	q = CreateQueue(l * l);	
	
	InitQueue(q, v[0].id);


	fprintf(stdout, "Starting a BFS...\n");

	while (q->start != q->end){
		int vertex = Dequeue(q);
		static float alpha = 0;
		fprintf(stdout, "Visiting the vertex: %i\n", vertex);

		fprintf(stdout, "Retrieving all adjacents vertex...\n");
		for (i = 0; i < l; i++){
			if (m[vertex - 1][i] == 1){
				/*angulo inicial*/
				if (visited[i] == 0){
					
					visited[i] = 1;

					fprintf(stdout, "Queueing the vertex: %i\n", i + 1);

					Queue(q, i + 1);

					v[i].depth = v[vertex - 1].depth + 1;


					fprintf(stdout, "I have %i vertex on my queue\n", q->end - q->start);

				}
			}
		}

		visited[vertex - 1] = 1;

		/*Calculo da posicao do filho*/
		v[vertex - 1].y = sin(alpha) * (v[vertex - 1].depth * RADIUS);
		v[vertex - 1].x = cos(alpha) * (v[vertex - 1].depth * RADIUS);

		fprintf(stdout, "Walking alpha (%.3f) %.3f degrees...\n", alpha, diff);
		alpha += diff;

		/*TODO: tratar caso em que alpha passa de 360*/

		fprintf(stdout, "Putting the vertex: %i at (%f, %f)\n", vertex, v[vertex - 1].x, v[vertex - 1].y);

	}
}

/*Funcao depreciada*/
#ifdef DEPREC
void ApplyForces(Vertice *v, int l, UINT **m){
	int i, j, k, li, c;
	int temp = 1000000;

	for (i = 0; i < ITERATIONS; i++){
		/*Calcula as forças de repulsão*/
		for (j = 0; j < l; j++){
			int u;
			/*inicializa a dispersão de cada vertice*/
			v[j].xdisp = 0;
			v[j].ydisp = 0;

			for (u = 0; u < l; u++){
				if (v[u].id != v[j].id){
					/*v[i] = v, v[u] = u*/
					/*vetor de diferencas de posicao, 0:x, 1:y*/
					int dif[2];
					float vs;

					/*v.x - u.x*/
					dif[0] = v[j].x - v[u].x;
					/*v.y - u.y*/
					dif[1] = v[j].y - v[u].y;

					/*Modulo do vetor diferenca*/
					vs = VectorSize(dif[0], dif[1]);

					/*Nova dispersao em x de v*/
					v[j].xdisp = v[j].xdisp + ((int)(dif[0]/vs) * RepForce(vs, l));

					/*Nova dispersao em x de v*/
					v[j].ydisp = v[j].ydisp + ((int)floor(dif[1]/vs)) * RepForce(vs, l);
				}
			}
		}

		/*Calcula as forcas de atracao*/
		for (li = 0; li < l; li++){
			for (c = 0; c < l; c++){				
				if (m[li][c] == 1){
					/*o: x; 1: y*/
					/*neste caso, m[li] representa o v da aresta, enquanto m[c] representa u*/
					int dif[2];
					/*diferença entre os dois vetores*/
					dif[0] = v[li].x - v[c].x;
					dif[1] = v[li].y - v[c].y;

					printf("Delta: (%i,%i) \n", dif[0], dif[1]);

					

					/*Calcula os valores de dispersao pra x e y de ambas extremidades da aresta*/
					v[li].xdisp = v[li].xdisp - (int)(2 * (dif[0]/VectorSize(dif[0], dif[1]) * AtrForce(VectorSize(dif[0], dif[1]), l)));
					v[c].ydisp = v[c].ydisp + (int)(2 * (dif[1]/VectorSize(dif[0], dif[1]) * AtrForce(VectorSize(dif[0], dif[1]), l)));
					m[c][li] = 0;
				}
			}
		}

		/*Limita a dispersao para dentro do frame e de uma determinada temperatura t*/
		for (k = 0; k < l; k++){
			/*Calcula a nova posicao de v*/
			int dvs = VectorSize(v[k].xdisp, v[k].ydisp);

			dvs = dvs == 0 ? 1 : dvs;

			/*printf("temperatura: %i\n", temp);
			printf("x: %i\n", v[k].x);
			printf("novo x: %i\n", v[k].x + (v[k].xdisp/dvs) * min(v[k].xdisp, temp));*/


			v[k].x = v[k].x + (v[k].xdisp/dvs) * min(v[k].xdisp, temp) * 10;
			v[k].y = v[k].y + (v[k].ydisp/dvs) * min(v[k].ydisp, temp) * 10;
			/*fim do calculo da nova posicao*/


			/*limita x dentro do frame*/
			v[k].x = min((int)floor(W/2), max((int)(floor(-W/2)), v[k].x));
			
			/*limita y dentro do frame*/
			v[k].y = min((int)floor(H/2), max((int)(floor(-H/2)), v[k].y));

			printf("Posicionando o vertice: %i, nas coordenadas (%.2f,%.2f)\n", v[k].id, v[k].x, v[k].y);
			
		}

		temp -= 10;
	}
}

int AtrForce(int x, int l){
	float k = sqrt(A/l);

	return (int)floor((double)(x*x/k));
}
#endif

int RepForce(int x, int l){
	int k = (int)floor(sqrt(A/l));
	
	return (int)floor((k*k)/x);
}


void StartDrawing(Graph *g){
	/*Cria o posicionamento inicial dos vertices*/
	InitialLayout(g->v, g->sizev, g->am->m);
}

void ApplyPhLaws(Graph *g){
	double energy;
	int vcount;

	do{
		energy = 0;
		/*Para cada vertice calcula lei de coulumb (atracao) e 
		lei de hook (repulsao)*/
		for (vcount = 0; vcount < g->sizev; vcount++){
			g->v[vcount].forces.x = g->v[v.count].forces.y = 0;
		}
	}while(energy > INCERCIA_STATUS)
}
#endif
