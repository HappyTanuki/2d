#ifndef _PZ_H
#define _PZ_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>

typedef struct _Point {
	int row;
	int column;
}Point;

#define KEY_UP		72
#define KEY_DOWN	80
#define KEY_RIGHT	77
#define KEY_LEFT	75
#define KEY_STOP	'q'
#define KEY_RESET	'r'

int		getKey();
void	init(Point* cPoint);
int		check(FILE* fp);
void	display(int key);
void	getIndex(int key, Point cPoint, Point* mPoint);
void	change(Point* cPoint, Point mPoint);
int		getLine();
int		play(Point* cPoint);
void	filewrite(FILE* fp, char* string);
void	Generate_save(FILE* fp);

#endif