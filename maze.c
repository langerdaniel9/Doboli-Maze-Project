#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "prototypes.h"

#define MAX_SIZE 30
#define MAX_NUMBER_OF_STEPS 30

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
int srandCall = 0;

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
	fprintf(output, "MARK\t\tMarked spot (%i, %i)\n", currentPos.x, currentPos.y);
}

void MOVE_F()
{
	// Move up one spot (↑) and mark previous square
	steps++;
	MARK();
	currentPos.y -= 1;
	fprintf(output, "MOVE_F\t\tMoved up to (%i, %i) | Step Count = %i\n", currentPos.x, currentPos.y, steps);
	checkIfOnDeed();
}

void MOVE_B()
{
	// Move down one spot (↓) and mark previous square
	steps++;
	MARK();
	currentPos.y += 1;
	fprintf(output, "MOVE_B\t\tMoved down to (%i, %i) | Step Count = %i\n", currentPos.x, currentPos.y, steps);
	checkIfOnDeed();
}

void MOVE_L()
{
	// Move left one spot (←) and mark previous square
	steps++;
	MARK();
	currentPos.x -= 1;
	fprintf(output, "MOVE_L\t\tMoved left to (%i, %i) | Step Count = %i\n", currentPos.x, currentPos.y, steps);
	checkIfOnDeed();
}

void MOVE_R()
{
	// Move right one spot (→) and mark previous square
	steps++;
	MARK();
	currentPos.x += 1;
	fprintf(output, "MOVE_R\t\tMoved right to (%i, %i) | Step Count = %i\n", currentPos.x, currentPos.y, steps);
	checkIfOnDeed();
}

int CWL() // check left
{
	fprintf(output, "CWL ()\n");
	if (mazeArray[(currentPos.x + (currentPos.y * x_dim)) - 1] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) - 1] == 0)
	{
		fprintf(output, "CWL\t\tLeft of (%i, %i) is empty\n", currentPos.x, currentPos.y);
		return 1;
	}
	fprintf(output, "CWL\t\tLeft of (%i, %i) is occupied\n", currentPos.x, currentPos.y);
	return 0;
}

int CWR() // check right
{
	fprintf(output, "CWR ()\n");
	if (mazeArray[(currentPos.x + (currentPos.y * x_dim)) + 1] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) + 1] == 0)
	{
		fprintf(output, "CWR\t\tRight of (%i, %i) is empty\n", currentPos.x, currentPos.y);
		return 1;
	}
	fprintf(output, "CWR\t\tRight of (%i, %i) is occupied\n", currentPos.x, currentPos.y);
	return 0;
}

int CWF() // check up
{
	fprintf(output, "CWF ()\n");
	if (mazeArray[(currentPos.x + (currentPos.y * x_dim)) - x_dim] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) - x_dim] == 0)
	{
		fprintf(output, "CWF\t\tUp of (%i, %i) is empty\n", currentPos.x, currentPos.y);
		return 1;
	}
	return 0;
	fprintf(output, "CWF\t\tUp of (%i, %i) is occupied\n", currentPos.x, currentPos.y);
}

int CWB() // check down
{
	fprintf(output, "CWB ()\n");
	if (mazeArray[(currentPos.x + (currentPos.y * x_dim)) + x_dim] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) + x_dim] == 0)
	{
		fprintf(output, "CWB\t\tDown of (%i, %i) is empty\n", currentPos.x, currentPos.y);
		return 1;
	}
	fprintf(output, "CWB\t\tDown of (%i, %i) is occupied\n", currentPos.x, currentPos.y);
	return 0;
}

void PUSH()
{
	if (stackPosition == MAX_SIZE)
	{
		CLEAR();
	}
	int i;
	stack[stackPosition] = currentPos;
	stackPosition++;
	fprintf(output, "PUSH\t\tPushed (%i, %i) to stack\n", currentPos.x, currentPos.y);
	fprintf(output, "Stack is now: ");
	for (i = 0; i < stackPosition; i++)
	{
		coord stackPos = stack[i];
		fprintf(output, "(%i, %i) ", stackPos.x, stackPos.y);
	}
	fprintf(output, "\n");
}

void POP()
{
	int i;
	stackPosition--;
	fprintf(output, "\tPOP Popped top of stack\n");
	fprintf(output, "Stack is now: ");
	for (i = 0; i < stackPosition; i++)
	{
		coord stackPos = stack[i];
		fprintf(output, "(%i, %i) ", stackPos.x, stackPos.y);
	}
	fprintf(output, "\n");
}

coord PEEK()
{
	int i;
	fprintf(output, "\tPEEK Peeked (%i, %i) from top of stack\n", stack[stackPosition - 1].x, stack[stackPosition - 1].y);
	return stack[stackPosition - 1];
}

void CLEAR()
{
	// Remove all but stored locations
	// Need to keep at least one because otherwise execution will just end since there are no possible moves, ie. only call when adding the max_size+1th location
	stackPosition = 0;
	int i;
	fprintf(output, "CLEAR\t\tCleared stack\n");
	fprintf(output, "Stack is now: ");
	for (i = 0; i < stackPosition; i++)
	{
		coord stackPos = stack[i];
		fprintf(output, "(%i, %i) ", stackPos.x, stackPos.y);
	}
	fprintf(output, "\n");
}

void BACKTRACK()
{
	// Only gets called if there are no more immediate possible moves, so if there is nothing stored in the stack then there are no moves left at all
	if (stackPosition == 0)
	{
		fprintf(output, "There are no possible moves\n");
		printf("There are no possible moves\n");
		exit(1);
	}
	steps++;
	MARK();
	fprintf(output, "BACKTRACK\tUsing PEEK:\n");
	coord jumpTo = PEEK();
	fprintf(output, "BACKTRACK\tUsing POP:\n");
	POP();
	currentPos.x = jumpTo.x, currentPos.y = jumpTo.y;
	fprintf(output, "BACKTRACK\tMoving back to peeked position (%i, %i) | Step Count = %i\n", currentPos.x, currentPos.y, steps);
}

void BJPI()
{
	if (CWL() == 1)
	{
		// i represents the number of spaces jumped over, or the number of consecutive CW functions used
		int i = 1;
		while (mazeArray[(currentPos.x + (currentPos.y * x_dim)) - i] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) - i] == 0)
		{
			// also in a jump, do we MARK all of the spaces the ant jumps over?
			MARK();
			currentPos.y -= 1;
			checkIfOnDeed();
			i++;
		}
		// in a jump, would that only take one step in the stack memory?
		steps++;
	}
	else if (CWR() == 1)
	{
		int i = 1;
		while (mazeArray[(currentPos.x + (currentPos.y * x_dim)) + i] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) + i] == 0)
		{
			MARK();
			currentPos.y += 1;
			checkIfOnDeed();
			i++;
		}
		steps++;
	}
	else if (CWF() == 1)
	{
		int i = 1;
		while (mazeArray[(currentPos.x + (currentPos.y * x_dim)) - (x_dim * i)] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) - (x_dim * i)] == 0)
		{
			MARK();
			currentPos.x += 1;
			checkIfOnDeed();
			i++;
		}
		steps++;
	}
	else if (CWB() == 1)
	{
		int i = 1;
		while (mazeArray[(currentPos.x + (currentPos.y * x_dim)) + (x_dim * i)] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) + (x_dim * i)] == 0)
		{
			MARK();
			currentPos.x -= 1;
			checkIfOnDeed();
			i++;
		}
		steps++;
	}

	fprintf(output, "BJPI ()\n");
}

void CJPI()
{
	if (CWL() == 1)
	{
		MOVE_L;
	}
	else if (CWR() == 1)
	{
		MOVE_R;
	}
	else if (CWF() == 1)
	{
		MOVE_F;
	}
	else if (CWB() == 1)
	{
		MOVE_B;
	}
	fprintf(output, "CJPI ()\n");
}

void RP(int n, int t)
{
}

//--------------------------------
// Other functions, will move to functions.h/functions.c file later

void findDims()
{
	// scan a single row to find x_dim
	char rowForRowDim[100];
	input = fopen("maze.txt", "r");

	fgets(rowForRowDim, 100, input);
	int i;
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
	// reopen file
	input = fopen("maze.txt", "r");

	// Scans the input file into the necessary arrays
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
		// check the left column
		if (mazeArray[i * x_dim] == ' ')
		{
			currentPos.x = 0, currentPos.y = i; // Good
			return;
		}
		// check the right column
		else if (mazeArray[(i * x_dim) + x_dim - 1] == ' ')
		{
			currentPos.x = x_dim - 1, currentPos.y = i; //
			return;
		}
	}

	// checks the top and bottom rows to check for the entrance
	for (i = 0; i < x_dim; i++)
	{
		// check the top row
		if (mazeArray[i] == ' ')
		{
			currentPos.x = i, currentPos.y = 0; // Good
			return;
		}
		// check the bottom row
		else if (mazeArray[((x_dim - 1) * y_dim) + i] == ' ')
		{
			currentPos.x = i, currentPos.y = x_dim - 1; // Good
			return;
		}
	}

	printf("starting position = (%i, %i)\n", currentPos.x, currentPos.y);
}

void checkSurroundings()
{
	// If there are more than 1 possible moves, save this coordinate to come back to later
	if (CWL() + CWF() + CWR() + CWB() > 1)
	{
		fprintf(output, "Multiple paths detected\n");
		PUSH();
	}

	// Use the priority to decide the general direction to head towards, with some random variation to keep the path different run to run
	switch (priority)
	{
	// Default priority, finds which direction to head towards, which gives you the relative location, ie top/right/bottom/left of maze, so prioritize moving towards the center. If you are at top of maze, only move is to go down, so continue to prioritize going generally downward
	case 0:
	{ // default
		if (CWL())
		{
			priority = 1;
			MOVE_L();
		}
		else if (CWF())
		{
			priority = 2;
			MOVE_F();
		}
		else if (CWR())
		{
			priority = 3;
			MOVE_R();
		}
		else if (CWB())
		{
			priority = 4;
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
	{ // generally ←
		bool moved = false;
		int rand = random(1, 4);
		switch (rand)
		{
		case 1:
		{
			if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			else if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			else if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			else if (CWR())
			{
				moved = true;
				MOVE_R();
			}

			break;
		}
		case 2:
		{
			if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			else if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			else if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			else if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			break;
		}
		case 3:
		{
			if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			else if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			else if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			else if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			break;
		}
		case 4:
		{
			if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			else if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			else if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			else if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			break;
		}
		}

		if (!moved)
		{
			BACKTRACK();
		}
	}
	break;

	case 2:
	{ // generally ↑
		bool moved = false;
		int rand = random(1, 4);
		switch (rand)
		{
		case 1:
		{
			if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			else if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			else if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			else if (CWB())
			{
				moved = true;
				MOVE_B();
			}

			break;
		}
		case 2:
		{
			if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			else if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			else if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			else if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			break;
		}
		case 3:
		{
			if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			else if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			else if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			else if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			break;
		}
		case 4:
		{
			if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			else if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			else if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			else if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			break;
		}
		}

		if (!moved)
		{
			BACKTRACK();
		}
	}
	break;

	case 3:
	{ // generally →
		bool moved = false;
		int rand = random(1, 4);
		switch (rand)
		{
		case 1:
		{
			if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			else if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			else if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			else if (CWL())
			{
				moved = true;
				MOVE_L();
			}

			break;
		}
		case 2:
		{
			if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			else if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			else if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			else if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			break;
		}
		case 3:
		{
			if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			else if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			else if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			else if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			break;
		}
		case 4:
		{
			if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			else if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			else if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			else if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			break;
		}
		}

		if (!moved)
		{
			BACKTRACK();
		}
	}
	break;

	case 4:
	{ // generally ↓
		bool moved = false;
		int rand = random(1, 4);
		switch (rand)
		{
		case 1:
		{
			if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			else if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			else if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			else if (CWF())
			{
				moved = true;
				MOVE_F();
			}

			break;
		}
		case 2:
		{
			if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			else if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			else if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			else if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			break;
		}
		case 3:
		{
			if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			else if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			else if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			else if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			break;
		}
		case 4:
		{
			if (CWL())
			{
				moved = true;
				MOVE_L();
			}
			else if (CWB())
			{
				moved = true;
				MOVE_B();
			}
			else if (CWR())
			{
				moved = true;
				MOVE_R();
			}
			else if (CWF())
			{
				moved = true;
				MOVE_F();
			}
			break;
		}
		}

		if (!moved)
		{
			BACKTRACK();
		}
	}
	break;
	}
}

void logic()
{
	// While there are steps available, check surroundings and move
	while (steps < MAX_NUMBER_OF_STEPS)
	{
		checkSurroundings();
	}
	// When out of steps, print point total
	fprintf(output, "\n\nPoint total is %i", deedTotal);
}

void reviewPriorities()
{
	int i;
	int m = stack2Position - 1;

	// First bubble sort stack2 by increasing point value
	bool sorted = false;
	deed temp;
	while (!sorted)
	{
		sorted = true;
		for (i = 0; i < m; i++)
		{
			if (stack2[i].value < stack2[i + 1].value)
			{
				temp = stack2[i];
				stack2[i] = stack2[i + 1];
				stack2[i + 1] = temp;
				sorted = false;
			}
		}
	}

	// If multiple are found to be true, then itll pick the one that is first in the order
	int left = 0, right = 0, up = 0, down = 0;

	for (i = 0; i < stack2Position - 1; i++)
	{
		// See if x continuously increases, if so then prioritize moving left
		if (stack2[i].location.x >= stack2[i + 1].location.x)
		{
			left++;
		}
		// See if x continuously decreases, if so then prioritize moving right
		else if (stack2[i].location.x <= stack2[i + 1].location.x)
		{
			right++;
		}
		// See if y continuously increases, if so then prioritize moving up
		else if (stack2[i].location.y <= stack2[i + 1].location.y)
		{
			up++;
		}
		// See if y continuously decreases, if so then prioritize moving down
		else if (stack2[i].location.y >= stack2[i + 1].location.y)
		{
			down++;
		}
	}

	if (left == m)
	{
		fprintf(output, "Changed priority from %i to 1\n", priority);
		priority = 1;
		return;
	}
	else if (right == m)
	{
		fprintf(output, "Changed priority from %i to 3\n", priority);
		priority = 3;
		return;
	}
	else if (up == m)
	{
		fprintf(output, "Changed priority from %i to 2\n", priority);
		priority = 2;
		return;
	}
	else if (down == m)
	{
		fprintf(output, "Changed priority from %i to 4\n", priority);
		priority = 4;
	}
}

void checkIfOnDeed()
{
	// Checks to see if you are on the same space as a deed
	if (deedArray[currentPos.x + (currentPos.y * x_dim)] > 0)
	{
		fprintf(output, "Found a Deed worth %i at (%i, %i)\n", deedArray[currentPos.x + (currentPos.y * x_dim)], currentPos.x, currentPos.y);
		// If so collect that point value
		deedTotal += deedArray[currentPos.x + (currentPos.y * x_dim)];
		// Add the location as well as deed value to stack2
		stack2[stack2Position].location = currentPos;
		stack2[stack2Position].value = deedArray[currentPos.x + (currentPos.y * x_dim)];
		// Remove the deed from the current spot (it has already been picked up, and cant be picked up multiple times)
		deedArray[currentPos.x + (currentPos.y * x_dim)] = 0;
		stack2Position++;
		// If you have collected at least two deeds, there is potential to find a pattern, so try to find a pattern for them
		if (stack2Position > 1)
		{
			reviewPriorities();
		}
	}
}

int random(int min, int max)
{
	// returns a random value between int min and int max, inclusive
	if (srandCall == 0)
	{
		srand(time(NULL));
		srandCall = 1;
	}

	return ((rand() % max) + min);
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
		if (pheromoneArray[i] == 1)
		{
			printf("|X|%i| ", deedArray[i]);
		}
		else
		{
			printf("|%c|%i| ", mazeArray[i], deedArray[i]);
		}
	}

	// print maze array
	// printMaze();

	// print deed array
	// printDeed();

	// print pheremone array
	// printPheromone();

	printf("\nPoint Total = %i\n", deedTotal);

	return 0;
}
