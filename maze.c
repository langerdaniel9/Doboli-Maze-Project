#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//--------------------------------
typedef struct coord
{
	int x;
	int y;
} coord;


coord currentPos;

typedef struct deed
{
	coord location;
	int value;
} deed;

char pher_maze[10][10] = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
//--------------------------------

// 17 main functions
// Change and fill in as needed, will move to stack.h/stack.c file later
void MARK() {
	pher_maze[currentPos.x][currentPos.y] = 1;
}

void MOVE_F() {
	currentPos.x += 1;
//	printf("(%i, %i)\n", currentPos.x, currentPos.y);
}

void MOVE_B() {
	currentPos.x -= 1;
//	printf("(%i, %i)\n", currentPos.x, currentPos.y);
}

void MOVE_L() {
	currentPos.y -= 1;
//	printf("(%i, %i)\n", currentPos.x, currentPos.y);
}

void MOVE_R() {
	currentPos.y += 1;
//	printf("(%i, %i)\n", currentPos.x, currentPos.y);
}

void CWL()
{
}

void CWR()
{
}

void CWF()
{
}

void CWB()
{
}

void PUSH()
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
}

void BJPI()
{
}

void CJPI()
{
}

void BACKTRACK()
{
}

void RP(int n, int t)
{
}

//--------------------------------
// Other functions

//--------------------------------

int main()
{
	// open input file
	FILE *input;

	if ((input = fopen("maze.txt", "r")) == NULL)
	{
		printf("error in opening maze.txt");
		exit(1);
	}

	int i, j;
	int x_dim, y_dim;

	// get starting position and maze dimensions from input file
	fscanf(input, "(%i, %i)", &currentPos.x, &currentPos.y);
	fscanf(input, "%i %i", &x_dim, &y_dim);
	// printf("(%i, %i)\n%i %i\n", starting_x, starting_y, x_dim, y_dim);
	
	MARK ();
	MOVE_F ();
	MARK ();
	MOVE_R ();
	MARK ();
	MOVE_B ();
	MARK ();
	MOVE_L ();
	MARK ();
	
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			printf("%i", pher_maze[i][j]);
		}
		printf("\n");
	}

/*
	// create both arrays
	// create maze array
	char *mazeArray = (char *)malloc(((x_dim) * (y_dim)) * sizeof(char *));

	// create deed array
	int *deedArray = (int *)malloc(((x_dim) * (y_dim)) * sizeof(int *));
	for (i = 0; i < (x_dim * y_dim); i++)
	{
		deedArray[i] = 0;
	}

	// some unintended behavior observed, so just reopen text file and read first two lines to start at the beginning of the maze
	fclose(input);
	input = fopen("maze.txt", "r");
	char garbage[100];
	fgets(garbage, 100, input);
	fgets(garbage, 100, input);

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

	return 0;
*/
}
