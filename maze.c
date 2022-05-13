#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 30
#define MAX_NUMBER_OF_STEPS 30

//--------------------------------
// global variables
typedef struct coord
{
	int x;
	int y;
} coord;

typedef struct deed
{
	coord location;
	int value;
} deed;

char *mazeArray;
int *deedArray;
int *pherArray;

int x_dim;
int y_dim;
int moves = 0;

coord stack[STACK_SIZE];
int stackPos;

coord currentPos;
FILE *output;

//--------------------------------
// 17 main functions
// Change and fill in as needed, will move to stack.h/stack.c file later
void MARK()
{
	pherArray[(currentPos.x * x_dim) + currentPos.y] = 1;
	fprintf(output, "Marked spot (%i, %i)\n", currentPos.x, currentPos.y);
}

void MOVE_F()
{
	currentPos.x += 1;
	MARK();
	moves++;
}

void MOVE_B()
{
	currentPos.x -= 1;
	MARK();
	moves++;
}

void MOVE_L()
{
	currentPos.y -= 1;
	MARK();
	moves++;
}

void MOVE_R()
{
	currentPos.y += 1;
	MARK();
	moves++;
}

int CWL()
{
	if (mazeArray[(currentPos.x * x_dim) + currentPos.y - 1] == ' ' && pherArray[(currentPos.x * x_dim) + currentPos.y - 1] == 0)
	{
		return 1;
	}
	return 0;
}

int CWR(char *mazeArray, coord currentPos, int x_dim)
{
	if (mazeArray[(currentPos.x * x_dim) + currentPos.y + 1] == ' ' && pherArray[(currentPos.x * x_dim) + currentPos.y + 1] == 0)
	{
		return 1;
	}
	return 0;
}

int CWF()
{
	if (mazeArray[((currentPos.x + 1) * x_dim) + currentPos.y] == ' ' && pherArray[((currentPos.x + 1) * x_dim) + currentPos.y] == 0)
	{
		return 1;
	}
	return 0;
}

int CWB()
{
	if (mazeArray[((currentPos.x - 1) * x_dim) + currentPos.y] == ' ' && pherArray[((currentPos.x - 1) * x_dim) + currentPos.y] == 0)
	{
		return 1;
	}
	return 0;
}

void PUSH(coord pos)
{
}

void POP()
{
}

void PEEK()
{
}

void CLEAR()
{
	stackPos = 0;
}

void BACKTRACK()
{
}

void BJPI()
{
}

void CJPI()
{
	if (CWL)
	{
		MOVE_L;
	}
	else if (CWR)
	{
		MOVE_R;
	}
	else if (CWF)
	{
		MOVE_F;
	}
	else if (CWB)
	{
		MOVE_B;
	}
}

void RP(int n, int t)
{
}

//--------------------------------
// Other functions

void createArrays(int x_dim, int y_dim)
{
	// create maze array
	mazeArray = (char *)malloc(((x_dim) * (y_dim)) * sizeof(char *));

	// create deed and pheremone array
	deedArray = (int *)malloc(((x_dim) * (y_dim)) * sizeof(int *));
	pherArray = (int *)malloc(((x_dim) * (y_dim)) * sizeof(int *));

	// initialize both to zero
	int i;
	for (i = 0; i < (x_dim * y_dim); i++)
	{
		deedArray[i] = 0;
		pherArray[i] = 0;
	}
}

void findStart()
{
	// check all x=0
	// check all y=0
	// check all x=x_dim-1
	// check all y=y_dim-1

	// currentPos.x = whatever;
	// currentPos.y = whatever;
}

int *checkSurroundings()
{
	CWL();
	CWR();

	return 1;
}

//--------------------------------

int main()
{
	/*
	int i, j;

		CWL(currentPos.x, currentPos.y);
		CWR(currentPos.x, currentPos.y);
		CWF(currentPos.x, currentPos.y);
		CWB(currentPos.x, currentPos.y);

		if (CWL(currentPos.x, currentPos.y) == 1) {
			printf("I feel an itch to the LEFT");
		} else if (CWR(currentPos.x, currentPos.y) == 1) {
			printf("I feel an itch to the RIGHT");
		} else if (CWF(currentPos.x, currentPos.y) == 1) {
			printf("I feel an itch FORWARD");
		} else if (CWB(currentPos.x, currentPos.y) == 1) {
			printf("I feel an itch BACKWARDS");
		}
	*/

	// open input file
	FILE *input;

	if ((input = fopen("maze.txt", "r")) == NULL)
	{
		printf("error in opening maze.txt");
		exit(1);
	}

	if ((output = fopen("output.txt", "w")) == NULL)
	{
		printf("error in opening maze.txt");
		exit(1);
	}

	int i, j;

	// scan a single row to find x_dim
	// fgets(rowForRowDim, 100, input);

	fclose(input);
	input = fopen("maze.txt", "r");

	// scan entire file to get y_dim
	// while(fgets(rowForRowDim, 100, input) != EOF) {
	// y_dim++;
	// }

	// some unintended behavior observed, so just reopen text file
	fclose(input);
	input = fopen("maze.txt", "r");

	// create arrays
	createArrays(x_dim, y_dim);

	// scan maze into array
	for (i = 0; i < x_dim; i++)
	{
		char line[1000];
		fgets(line, 1000, input);

		int l = 0;
		for (j = 0; j < strlen(line); j++)
		{
			// if its a number (deed value)
			if (isdigit(line[j]))
			{
				char temp[100];
				int k = 0;
				do
				{
					temp[k] = line[j];
					temp[k + 1] = '\0';
					k++;
					j++;
				} while (isdigit(line[j]));
				j--;
				deedArray[(i * x_dim) + l] = atoi(temp);
				mazeArray[(i * x_dim) + l] = ' ';
				l++;
				// otherwise its a wall or a space
			}
			else if (line[j] == '*' || line[j] == ' ')
			{
				mazeArray[(i * x_dim) + l] = line[j];
				l++;
			}
		}
	}

	// get starting position and maze dimensions from input file
	findStart();

	// print maze array
	for (i = 0; i < x_dim; i++)
	{
		for (j = 0; j < y_dim; j++)
		{
			printf("%c", mazeArray[(i * x_dim) + j]);
		}
		printf("\n");
	}
	printf("\n\n");

	// print deed array
	for (i = 0; i < x_dim; i++)
	{
		for (j = 0; j < y_dim; j++)
		{
			printf("%i ", deedArray[(i * x_dim) + j]);
		}
		printf("\n");
	}
	printf("\n\n");

	// print pheremone array
	for (i = 0; i < x_dim; i++)
	{
		for (j = 0; j < y_dim; j++)
		{
			pherArray[(i * x_dim) + j] = 0;
			printf("%i ", pherArray[(i * x_dim) + j]);
		}
		printf("\n");
	}

	return 0;
}
