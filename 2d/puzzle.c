#include "pz.h"

int**	pz;
int		count;
int		maxCount;
char	username[30];
int		pz_pow_size, pz_size;

int main(int argc, char* argv[]) {
	char input = 0;
	int result, i;
	FILE* fp = NULL;

	Point cPoint;

	pz_size = 3;

	if (argc > 1)
		pz_size = atoi(argv[1]);

	srand((unsigned int)time(NULL));

	pz_pow_size = (int)pow(pz_size, 2);

	pz = (int **)malloc(sizeof(int*) * pz_size);
	for (i=0; i<pz_size; i++)
		pz[i] = (int*)malloc(sizeof(int) * pz_size);

	if (pz == NULL)
		return 0;
	for (i = 0; i < pz_size; i++)
		if (pz[i] == NULL)
			return 0;

	init(&cPoint);
	display(0);

	for (;;) {
		result = play(&cPoint);
		
		if (check(fp) || result != 1) {
			if (result == 1 || result == 0) {
				if (result == 1)
					printf("Finish\n");
				else
					printf("Fail\n");
				printf("continue? (y/n) : ");
				scanf(" %c", &input);
			}
			if (input == 'y' || result == KEY_RESET) {
				init(&cPoint);
				display(0);
				continue;
			}
			else
				break;
		}
	}
	if (pz != NULL) {
		for (i = 0; i < pz_size; i++)
			free(pz[i]);
		free(pz);
		pz = NULL;
	}

	return 0;
}