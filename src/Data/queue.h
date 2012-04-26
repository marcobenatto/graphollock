#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/*typedef struct node{
	int v;
	struct node *next;
}node;

typedef struct queue{
	node *head;
	node *last;
	int size;
}queue;*/

typedef struct queue{
	int start;
	int end;
	int size;
	int *data;
}queue;

queue *CreateQueue(int);
void InitQueue(queue *, int);
void Queue(queue *, int);
int Dequeue(queue *);
void DestroyQueue(queue *);
