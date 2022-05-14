#include <stdio.h>
#include <stdlib.h>
#include "prototypes.h"
#include "main_17.c"
#include "other_functions.c"

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

	// get starting position from input file
	findStart();

	// main logic function
	logic();
}
