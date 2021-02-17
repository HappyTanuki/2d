#include "pz.h"

extern int**	pz;
extern int		count;
extern int		maxCount;
extern char		username[30];
extern int		pz_pow_size, pz_size;

int play(Point* cPoint) {
	int key;
	Point mPoint;

	key = getKey();

	if (count >= maxCount)
		return 0;
	if (key == KEY_STOP)
		return KEY_STOP;
	else if (key == KEY_RESET)
		return KEY_RESET;

	getIndex(key, *cPoint, &mPoint);
	change(cPoint, mPoint);
	count++;
	display(key);

	return 1;
}

void change(Point* cPoint, Point mPoint) {
	int temp;

	temp = pz[cPoint->row][cPoint->column];
	pz[cPoint->row][cPoint->column] = pz[mPoint.row][mPoint.column];
	pz[mPoint.row][mPoint.column] = temp;

	cPoint->row = mPoint.row;
	cPoint->column = mPoint.column;
}

void getIndex(int key, Point cPoint, Point* mPoint) {

	mPoint->row = cPoint.row;
	mPoint->column = cPoint.column;

	switch (key) {
	case KEY_UP:
		if (cPoint.row > 0)
			mPoint->row = cPoint.row - 1;
		break;
	case KEY_DOWN:
		if (cPoint.row < pz_size - 1)
			mPoint->row = cPoint.row + 1;
		break;
	case KEY_RIGHT:
		if (cPoint.column < pz_size - 1)
			mPoint->column = cPoint.column + 1;
		break;
	case KEY_LEFT:
		if (cPoint.column > 0)
			mPoint->column = cPoint.column - 1;
		break;
	}
}

int check(FILE* fp) {
	int i;

	for (i = 0; i < pz_pow_size - 1; i++) {
		if (pz[i / pz_size][i % pz_size] != i + 1)
			return 0;
	}
	Generate_save(fp);

	return 1;
}

void display(int key) {
	int i, j;
	char* inputkey;

	system("cls");

	printf("忙式式式式成");
	for (i = 0; i < pz_size - 2; i++)
		printf("式式式式成");
	printf("式式式式忖\n");

	for (j = 0; j < pz_size; j++) {
		for (i = 0; i < pz_size; i++)
			if (pz[j][i] != 0)
				printf("弛%4d", pz[j][i]);
			else
				printf("弛%4s", "*");
		printf("弛\n");
		if (j < pz_size - 1) {
			printf("戍式式式式托");
			for (i = 0; i < pz_size - 2; i++)
				printf("式式式式托");
			printf("式式式式扣\n");
		}
	}
	printf("戌式式式式扛");
	for (i = 0; i < pz_size - 2; i++)
		printf("式式式式扛");
	printf("式式式式戎\n");


	switch (key) {
	case KEY_UP:
		inputkey = "UP";
		break;
	case KEY_DOWN:
		inputkey = "DOWN";
		break;
	case KEY_RIGHT:
		inputkey = "RIGHT";
		break;
	case KEY_LEFT:
		inputkey = "LEFT";
		break;
	default:
		inputkey = "NO";
		break;
	}
	printf("input : %s\n", inputkey);
	printf("count: %d\n", count);
}

void init(Point* cPoint) {
	int i, k;

	system("cls");
	printf("input max count: ");
	scanf("%d", &maxCount);

	printf("input your name: ");
	scanf("%s", &username);

	for (i = 0; i < pz_pow_size; i++) {
		pz[i / pz_size][i % pz_size] = rand() % pz_pow_size;

		for (k = 0; k < i; k++) {
			if (pz[i / pz_size][i % pz_size] == pz[k / pz_size][k % pz_size]) {
				i--;
				break;
			}
		}
		if (pz[i / pz_size][i % pz_size] == 0) {
			cPoint->row = i / pz_size;
			cPoint->column = i % pz_size;
		}
	}

	// for test
	for (i = 0; i < pz_pow_size - 1; i++) {
		pz[i / pz_size][i % pz_size] = i + 1;
	}
	pz[pz_size - 1][pz_size - 1] = pz_pow_size - 1;
	pz[pz_size - 1][pz_size - 2] = 0;
	cPoint->row = pz_size - 1;
	cPoint->column = pz_size - 2;
	//

	count = 0;
}

int getKey() {
	int key;

	key = getch();
	if (key == 224) {
		key = getch();
	}

	return key;
}

int getLine() {
	char buff[30] = { 0 };
	int length = 0;

	scanf("%s", buff);
	length = strlen(buff);
	if (length > 0 && length < 6) {
		if (!strcmp(buff, "up"))
			return KEY_UP;
		if (!strcmp(buff, "down"))
			return KEY_DOWN;
		if (!strcmp(buff, "right"))
			return KEY_RIGHT;
		if (!strcmp(buff, "left"))
			return KEY_LEFT;
		if (!strcmp(buff, "q"))
			return KEY_STOP;
	}
	return 0;
}

void	filewrite(FILE* fp, char* string) {
	char flac = 0;

	fp = fopen("score001.txt", "r");

	if (fp == NULL) {
		fp = fopen("score001.txt", "w");
		flac = 1;
	}
	else {
		fclose(fp);
		fp = fopen("score001.txt", "a");
		flac = 0;
	}

	if (flac) {
		fprintf(fp, "%10s %10s %10s %10s\n", "date", "time", "name", "count");
		fprintf(fp, "-------------------------------------------\n");
	}

	fprintf(fp, string);

	fclose(fp);

	return;
}

void	Generate_save(FILE* fp) {
	char date[100] = { 0 };
	char time[100] = { 0 };
	char string[1000] = { 0 };
	char c_count[100] = { 0 };

	_strdate(date);
	_strtime(time);

	sprintf(string, "%10s %10s %10s %10d\n", date, time, username, count);

	filewrite(fp, string);

	return;
}