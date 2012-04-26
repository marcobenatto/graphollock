#include "CrossCount.h"

#ifdef CROSSTEST
int main(int argc, char **argv){
	Point a, b, c, d;
	bool retorno;

	printf("Entre com dois pontos do segmento:\n");
	scanf("%i %i", &(a.x), &(a.y));	
	scanf("%i %i", &(b.x), &(b.y));		
	scanf("%i %i", &(c.x), &(c.y));
	scanf("%i %i", &(d.x), &(d.y));

/*	printf("Pontos:\n A=(%i,%i), B=(%i,%i), C=(%i, %i)\n", a.x, a.y, b.x, b.y, c.x, c.y);*/

	retorno = HaveCrossing(a, b, c, d);

	if ( retorno == true)
		printf("Cruza\n");
	else
		printf("Nãocruza\n");
}
#endif

bool Left(Point a, Point b, Point c){
	/*caso em que o segmento nao e horizontal*/
	if (a.y != b.y)
		return (c.x <= a.x && c.x <= b.x) ? true : false;
	else
		return (c.y <= a.y && c.y <= b.y) ? true : false;	
}

/*Determina se ha cruzamento entre dois segmentos AB, CD*/
bool HaveCrossing(Point a, Point b, Point c, Point d){
	return (Left(a, b, c) ^ Left(a, b, d)) && (Left(c, d, a) ^ Left(c, d, b));
}
