#include "../filecore.h"

typedef enum EventType{
	/*Inicio de aresta*/
	einit = 'I',
	/*Fim de aretsa*/
	eend = 'E'
}EventType;

/*Representa uma aresta*/
typedef struct Edge{
	UINT id;
	UINT endpoint1;
	UINT endpoint2;
}Edge;


/*Estruturas necessarias para implementacao de jornal
  e agenda*/
/*typedef struct Node{
	Edge e;
	EventType event;
	struct Node *next;
	struct Node *prev;
}Node;

typedef struct EventList{
	Node *head;
	Node *tail;
	UINT size;
}EventList;*/

/*Informacao do evento*/
typedef struct EventInformation{
	Edge *e;
	EventType etype;
}EventInformation;

/*EID = Edge ID*/
typedef EventInformation* Sched;
typedef UINT EID;
typedef EID* NPaper;


/*Funcoes*/
void DestroySched(Sched*);
Sched *CreateSched(int);

/*Estrutura antiga*/
/*Definindo jornal e lista*/
/*typedef EventList Newspapper;
typedef EventList Sched;

 *Funcoes de jornal
Newspapper *CreateNP(Edge, EventType);
void InsertEvent(Newspapper*, Edge, EventType);
Node *GetNodeAt(Newspapper *np, int index);*/
