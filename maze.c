#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "prototypes.h"

#define MAX_SIZE 30
#define MAX_NUMBER_OF_STEPS 2

//--------------------------------
// global variables
/*typedef struct coord
{
	int x;
	int y;
} coord;

typedef struct deed
{
	coord location;
	int value;
} deed;*/

char *mazeArray;
int *deedArray;
int *pheromoneArray;

int x_dim = 0, y_dim = 0;
coord currentPos;
int priority = 0;
int steps = 0;
int deedTotal = 0;

coord stack[MAX_SIZE];
int stackPosition = 0;

deed stack2[100];
int stack2Position = 0;

FILE *output;
FILE *input;

//--------------------------------
// 17 main functions, will move to main17.h/main17.c file later
void MARK()
{
	pheromoneArray[currentPos.x + currentPos.y * x_dim] = 1;
	fprintf(output, "Marked spot (%i, %i)\n", currentPos.x, currentPos.y);
}

void MOVE_F()
{
	MARK();
	currentPos.x += 1;
	checkIfOnDeed();
	steps++;
}

void MOVE_B()
{
	MARK();
	currentPos.x -= 1;
	checkIfOnDeed();
	steps++;
}

void MOVE_L()
{
	MARK();
	currentPos.y -= 1;
	checkIfOnDeed();
	steps++;
}

void MOVE_R()
{
	MARK();
	currentPos.y += 1;
	checkIfOnDeed();
	steps++;
}

int CWL() // check left
{
	if (mazeArray[(currentPos.x + (currentPos.y * x_dim)) - 1] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) - 1] == 0)
	{
		return 1;
	}
	return 0;
}

int CWR() // check right
{
	if (mazeArray[(currentPos.x + (currentPos.y * x_dim)) + 1] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) + 1] == 0)
	{
		return 1;
	}
	return 0;
}

int CWF() // check up
{
	if (mazeArray[(currentPos.x + (currentPos.y * x_dim)) - x_dim] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) - x_dim] == 0)
	{
		return 1;
	}
	return 0;
}

int CWB() // check down
{
	if (mazeArray[(currentPos.x + (currentPos.y * x_dim)) + x_dim] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) + x_dim] == 0)
	{
		return 1;
	}
	return 0;
}

void PUSH()
{
	stack[stackPosition] = currentPos;
	stackPosition++;
}

void POP()
{
	stackPosition--;
}

coord PEEK()
{
	return stack[stackPosition - 1];
}

void CLEAR()
{
	stackPosition = 0;
}

void BACKTRACK()
{
	coord jumpTo = PEEK();
	POP();
	currentPos.x = jumpTo.x, currentPos.y = jumpTo.y;
	steps++;
}

// void BJPI(){}

// void CJPI(){}

// void RP(int n, int t){}

//--------------------------------
// Other functions, will move to functions.h/functions.c file later

void findDims()
{
	int i;
	// scan a single row to find x_dim
	char rowForRowDim[100];
	input = fopen("maze.txt", "r");

	fgets(rowForRowDim, 100, input);
	for (i = 0; i < strlen(rowForRowDim); i++)
	{
		if (rowForRowDim[i] == '*' || rowForRowDim[i] == ' ')
		{
			x_dim++;
		}
		else if (isdigit(rowForRowDim[i]))
		{
			while (isdigit(rowForRowDim[i + 1]))
			{
				i++;
			}
			x_dim++;
		}
	}
	fclose(input);

	// scan entire file to get y_dim
	input = fopen("maze.txt", "r");
	while (fgets(rowForRowDim, 100, input) != NULL)
	{
		y_dim++;
	}
	fclose(input);

	// reopen file again
	input = fopen("maze.txt", "r");
}

void createArrays()
{
	// create maze array
	mazeArray = (char *)malloc(((x_dim) * (y_dim)) * sizeof(char *));

	// create deed and pheremone array
	deedArray = (int *)malloc(((x_dim) * (y_dim)) * sizeof(int *));
	pheromoneArray = (int *)malloc(((x_dim) * (y_dim)) * sizeof(int *));

	// initialize both to zero
	int i;
	for (i = 0; i < (x_dim * y_dim); i++)
	{
		deedArray[i] = 0;
		pheromoneArray[i] = 0;
	}
}

void scan()
{
	int i, j;
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
				deedArray[l + (x_dim * i)] = atoi(temp);
				mazeArray[l + (x_dim * i)] = ' ';
				l++;
				// otherwise its a wall or a space
			}
			else if (line[j] == '*' || line[j] == ' ')
			{
				mazeArray[l + (x_dim * i)] = line[j];
				l++;
			}
		}
	}
}

void findStart()
{
	int i;

	// checks the left and right columns to check for the entrance
	for (i = 0; i < y_dim; i++)
	{
		// top row
		if (mazeArray[i * x_dim] == ' ')
		{
			printf("here1 %i\n", i);			// top row
			currentPos.x = 0, currentPos.y = i; // Good
			return;
		}
		// bottom row
		else if (mazeArray[(i * x_dim) + x_dim - 1] == ' ')
		{
			printf("here2 %i\n", i);					// bottom row
			currentPos.x = x_dim - 1, currentPos.y = i; // Good
			return;
		}
	}

	// checks the top and bottom rows to check for the entrance
	for (i = 0; i < x_dim; i++)
	{
		// check the top row
		if (mazeArray[i] == ' ')
		{
			printf("here3 %i\n", i);
			currentPos.x = y_dim, currentPos.y = i;
			return;
		}
		// check the bottom row
		else if (mazeArray[(i * y_dim) + i] == ' ')
		{
			printf("here4 %i\n", i); // Left column & right column
			currentPos.x = x_dim, currentPos.y = i + 1;
			return;
		}
	}

	printf("starting position = (%i, %i)\n", currentPos.x, currentPos.y);
}

void checkSurroundings()
{
	printf("current position = %i, %i\n", currentPos.x, currentPos.y);
	if (CWL() + CWF() + CWR() + CWB() > 1)
	{
		PUSH();
	}

	switch (priority)
	{
	case 0:
	{ // default
		if (CWL)
		{
			priority = 1;
			MOVE_L();
		}
		else if (CWF)
		{
			priority = 3;
			MOVE_F();
		}
		else if (CWR)
		{
			priority = 5;
			MOVE_R();
		}
		else if (CWB)
		{
			priority = 7;
			MOVE_B();
		}
		else
		{
			printf("There are no possible moves\n");
			exit(1);
		}
	}
	break;

	case 1:
	{ // gradient ←
		if (CWL)
		{
			MOVE_L();
		}
		else if (CWF)
		{
			MOVE_F();
		}
		else if (CWB)
		{
			MOVE_B();
		}
		else if (CWR)
		{
			MOVE_R();
		}
		else
		{
			BACKTRACK();
		}
	}
	break;

	case 3:
	{ // gradient ↑
		if (CWF)
		{
			MOVE_F();
		}
		else if (CWL)
		{
			MOVE_L();
		}
		else if (CWR)
		{
			MOVE_R();
		}
		else if (CWB)
		{
			MOVE_B();
		}
		else
		{
			BACKTRACK();
		}
	}
	break;

	case 5:
	{ // gradient →
		if (CWR)
		{
			MOVE_R();
		}
		else if (CWF)
		{
			MOVE_F();
		}
		else if (CWB)
		{
			MOVE_B();
		}
		else if (CWL)
		{
			MOVE_L();
		}
		else
		{
			BACKTRACK();
		}
	}
	break;

	case 7:
	{ // gradient ↓
		if (CWB)
		{
			MOVE_B();
		}
		else if (CWL)
		{
			MOVE_L();
		}
		else if (CWR)
		{
			MOVE_R();
		}
		else if (CWF)
		{
			MOVE_F();
		}
		else
		{
			BACKTRACK();
		}
	}
	break;
	}
}

void logic()
{
	while (steps < MAX_NUMBER_OF_STEPS)
	{
		checkSurroundings();
	}
}

void reviewPriorities()
{
}

void checkIfOnDeed()
{
	if (deedArray[currentPos.x + (currentPos.y * x_dim)] > 0)
	{
		deedTotal += deedArray[currentPos.x + (currentPos.y * x_dim)];
		stack2[stack2Position].location = currentPos;
		stack2[stack2Position].value = deedArray[currentPos.x + (currentPos.y * x_dim)];
		stack2Position++;
		if (stack2Position > 1)
		{
			reviewPriorities();
		}
	}
}

void printMaze()
{
	int i, j;
	for (i = 0; i < x_dim; i++)
	{
		for (j = 0; j < y_dim; j++)
		{
			printf("%c", mazeArray[i + (j * x_dim)]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void printDeed()
{
	int i, j;
	for (i = 0; i < y_dim; i++)
	{
		for (j = 0; j < x_dim; j++)
		{
			printf("%i ", deedArray[i + j * x_dim]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void printPheromone()
{
	int i, j;
	for (i = 0; i < y_dim; i++)
	{
		for (j = 0; j < x_dim; j++)
		{
			printf("%i ", pheromoneArray[i + j * x_dim]);
		}
		printf("\n");
	}
	printf("\n\n");
}
//--------------------------------

int main()
{
	// open input file
	if ((input = fopen("maze.txt", "r")) == NULL)
	{
		printf("error in opening maze.txt");
		exit(1);
	}

	// create output file
	if ((output = fopen("output.txt", "w")) == NULL)
	{
		printf("error in opening maze.txt");
		exit(1);
	}

	int i, j;

	// get x_dim and y_dim
	findDims();

	// create arrays
	createArrays();

	// scan maze into array
	scan();

	// get starting position and maze dimensions from input file
	findStart();

	// main logic function
	logic();

	for (i = 0; i < x_dim * y_dim; i++)
	{
		if (i % (x_dim) == 0)
		{
			printf("\n");
		}
		printf("%c ", mazeArray[i]);
	}

	// print maze array
	// printMaze();

	// print deed array
	// printDeed();

	// print pheremone array
	// printPheromone();

	// printf("Point Total = %i\n", deedTotal);

	return 0;
}
