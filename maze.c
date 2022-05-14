#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "prototypes.h"
#include "main_17.c"
#include "other_functions.c"

#define MAX_SIZE 30
#define MAX_NUMBER_OF_STEPS 30

//--------------------------------

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
	printf("\n");
	// printMaze();

	// get starting position and maze dimensions from input file
	findStart();

	// main logic function
	logic();

	// print maze array
	printMaze();

	// print deed array
	// printDeed();

	// print pheremone array
	// printPheromone();

	// printf("\nPoint Total = %i\n", deedTotal);

	printf("x = %i, y = %i\n", x_dim, y_dim);
	return 0;
}
