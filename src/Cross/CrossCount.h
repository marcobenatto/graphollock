#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0

typedef int bool;

typedef struct Point{
	int x;
	int y;
}Point;

bool Left(Point, Point, Point);
bool HaveCrossing(Point, Point, Point, Point);
