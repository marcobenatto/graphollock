#ifdef DEPREC
#include "filecore.h"
#include "Data/gstructs.h"
#include "Data/queue.h"
#include <math.h>

#define W 800
#define H 600
#define A 480000
#define RADIUS 100
#define INERCIA_STATUS 0.05 /*O sistema possui pouca energia, logo os vertices
							  terao uma movimentacao minima, hora de parar.*/


float VectorSize(int,int);

void InitialLayout(Vertice*, int l, UINT**);

#ifdef DEPREC
void ApllyForces(Vertice*, int, UINT**);
#endif

int AtrForce(int, int);

int RepForce(int, int);

#endif
