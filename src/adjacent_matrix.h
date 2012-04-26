#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <errno.h>

#ifndef H_ADJACENT_MATRIX_H
#define H_ADJACENT_MATRIX_H

/* allocate and return a adjacent matrix */
unsigned int **allocate_matrix(int, int);
void destroy_matrix(unsigned int **, int, int);
void complete_matrix(FILE*, unsigned int **, int, int);
int order_of_matrix(FILE*);
void print_matrix(unsigned int **, int, int);
void handle_line(unsigned int **, char *, int, int);

#endif
