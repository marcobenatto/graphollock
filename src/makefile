all: adjacent_matrix.o drawing_core.o main.o Data/queue.o Data/gstructs.o Data/graphlib.o
	gcc -o graphollock main.o adjacent_matrix.o drawing_core.o Data/queue.o Data/gstructs.o Data/graphlib.o -lm -ggdb

#filecore.o: filecore.h
#	gcc -c filecore.c 

adjacent_matrix.o: adjacent_matrix.h
	gcc -c adjacent_matrix.c

drawing_core.o: drawing_core.h adjacent_matrix.h
	gcc -c drawing_core.c

main.o: drawing_core.h adjacent_matrix.h
	gcc -c main.c

queue.o: Data/queue.h
	gcc -c Data/queue.c

gstructs.o: Data/gstructs.h
	gcc -c Data/gstructs.c

graphlib.o: Data/graphlib.h
	gcc -c Data/graphlib.c

clean:
	rm graphollock main.o drawing_core.o adjacent_matrix.o Data/queue.o Data/gstructs.o Data/graphlib.o filecore.o

DQ:
	gcc -o Data/queue Data/queue.c -DDEBUGQUEUE

