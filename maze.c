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

typedef struct deed
{
	coord location;
	int value;
} deed;

char test_maze[10][10] = {
{'*', ' ', '*', '*', '*', '*', '*', '*', '*', '*'},
{'*', ' ', '*', '*', '*', '*', '*', '*', '*', '*'},
{'*', ' ', '*', '*', '*', '*', '*', '*', '*', '*'},
{'*', ' ', '*', '*', '*', '*', '*', '*', '*', '*'},
{'*', ' ', '*', '*', '*', '*', '*', '*', '*', '*'},
{'*', ' ', '*', '*', '*', '*', '*', '*', '*', '*'},
{'*', ' ', '*', '*', '*', '*', '*', '*', '*', '*'},
{'*', ' ', '*', '*', '*', '*', '*', '*', '*', '*'},
{'*', ' ', '*', '*', '*', '*', '*', '*', '*', '*'},
{'*', ' ', '*', '*', '*', '*', '*', '*', '*', '*'}};

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
	pherArray[currentPos.x][currentPos.y] = 1;
}

void MOVE_F()
{
}

void MOVE_B()
{
}

void MOVE_L()
{
}

void MOVE_R()
{
}

void CWL() {
	if ((currentPos.y - 1) == ' ' && pher_maze[x][y - 1] == 0) {
		printf("I feel an itch to the LEFT\n");
		return 1;
	} else {
		printf("I feel NO ITCH\n");
		return 0;
	}	
}

void CWR() {
	if ((currentPos.y + 1) == ' ' && pher_maze[x][y + 1] == 0) {
		printf("I feel an itch to the RIGHT\n");
		return 1;
	} else {
		printf("I feel NO ITCH\n");
		return 0;
	}
}

void CWF() {
	if ((currentPos.x + 1) == ' ' && pher_maze[x + 1][y] == 0) {
		printf("I feel an itch FORWARD\n");
		return 1;
	} else {
		printf("I feel NO ITCH\n");
		return 0;
	}
}

void CWB() {
	if ((currentPos.x - 1) == ' ' && pher_maze[x - 1][y] == 0) {
		printf("I feel an itch BACKWARDS\n");
		return 1;
	} else {
		printf("I feel NO ITCH\n");
		return 0;
	}
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
	/*
	int i, j; 
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			printf("%c", test_maze[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			printf("%i", pher_maze[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
	*/
	
//	coord currentPos;
//	currentPos.x = 0;
//	currentPos.y = 1;

/*	
	if (test_maze[currentPos.x][currentPos.y] != ' ') {
		printf("You're in a wall, buddy!\n");
		return 1;
	} else {
		printf("You're good! Here's your starting position: (%i, %i)\n", currentPos.x, currentPos.y);
	}
	
	CWL(currentPos.x, currentPos.y);
	CWR(currentPos.x, currentPos.y);
	CWF(currentPos.x, currentPos.y);
	CWB(currentPos.x, currentPos.y);

*/
/*	
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

	int i, j;
	int x_dim, y_dim;
	coord currentPos;

	// get starting position and maze dimensions from input file
	fscanf(input, "(%i, %i)", &currentPos.x, &currentPos.y);
	fscanf(input, "%i %i", &x_dim, &y_dim);
	// printf("(%i, %i)\n%i %i\n", starting_x, starting_y, x_dim, y_dim);

	// create both arrays
	// create maze array
	char *mazeArray = (char *)malloc(((x_dim) * (y_dim)) * sizeof(char *));

	// create deed array
	int *deedArray = (int *)malloc(((x_dim) * (y_dim)) * sizeof(int *));
	for (i = 0; i < (x_dim * y_dim); i++)
	{
		deedArray[i] = 0;
	}

	// creating pheremone array (initally all values into 0)	
	int *pherArray = (int *)malloc(((x_dim) * (y_dim)) * sizeof(int *));
	for (i = 0; i < (x_dim * y_dim); i++) {
		pherArray[i] = 0;
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
	printf("\n\n");
		
	// print pheremone array
	for (i = 0; i < x_dim; i++) {
		for (j = 0; j < y_dim; j++) {
			pherArray[(i * x_dim) + j] = 0;
			printf("%i ", pherArray[(i * x_dim) + j]);
		}
		printf("\n");
	}	
	
	return 0;

}
