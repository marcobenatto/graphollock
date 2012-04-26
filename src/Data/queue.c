#include "queue.h"

queue *CreateQueue(int s){
	queue *q = (queue*)malloc(sizeof(queue));
	
	q->data = (int*)malloc(s * sizeof(int));
	q->start = 0;
	q->end = 0;
	q->size = s;
	

	return q;
}

void Queue(queue *q, int v){
	/*Caso em que o final da pilha ultrapassa o tamanho dela. Não existe espaco suficientepara a insercao de um novo valor*/
	if (q->end >= q->size){
		fprintf(stderr, "Don't have space enought in the queue...fisinhing....\n");
		exit(ENOMEM);
	}

	q->data[q->end++] = v;	
}

int Dequeue(queue *q){
	if (q->start >= q->end){
		fprintf(stderr, "Don't have space enought in the queue...fisinhing....\n");
		exit(ENOMEM);
	}

	return q->data[q->start++];
}

void DestroyQueue(queue *q){
	free(q->data);
	free(q);
}

void InitQueue(queue *q, int v){
	q->data[0] = v;
	q->start = 0;
	q->end = 1;
}

#ifdef DEBUGQUEUE
void print(queue *q){
	node *n;
	n = q->head;

	for (n = q->head; n != q->last; n = n->next){
		printf("%i\n", n->v);
	}
	
	printf("last value: %i\n", q->last->v);
}

int main(){
	queue *q = CreateQueue(1);
	int i;
	
	for (i = 2; i <= 10; i++)
		Queue(q, i);

	print(q);

	printf("Dequeing...\n--------------------------------------\n");

	while(q->size != 0){
		int n = Dequeue(q);
		printf("Value: %i\n", n);
	}
}
#endif
