#include <stdio.h>
#include <stdlib.h>






int main() {
	FILE *maze; 
	
	if ((maze = fopen("maze.txt", "r")) == NULL) {
		printf("error in opening maze.txt");
		exit(1);
	} 


/*
	int i, j;
	int starting_x, starting_y;
	int x_dim, y_dim;
	char value;
	
	fscanf(maze, "(%i, %i)", &starting_x, &starting_y);
	fscanf(maze, "%i %i", &x_dim, &y_dim);
	
	printf("(%i, %i)\n%i %i", starting_x, starting_y, x_dim, y_dim);
	
	char actual_maze[(x_dim) * (y_dim)];
	char *point_maze[(x_dim) * (y_dim)];
	point_maze[(x_dim) * (y_dim)] = &actual_maze[(x_dim) * (y_dim)];
	*point_maze = (char*) malloc (((x_dim) * (y_dim)) * sizeof(char));

//	actual_maze[22] = '*';
//	printf("\n%c", actual_maze[22]);
	
	printf("\nmaze = %i, char = %i", sizeof(actual_maze), sizeof(char));
	
	
	/// Trying to scan maze into point_maze ///
		
	for (i = 0; i < x_dim; i++) {
		for (j = 0; j < y_dim; j++) {
			fscanf(maze, "%s\t", &value);
			point_maze[i][j] = value;
		}
	}

	/// Trying to print maze into console ///
	
	for (i = 0; i < x_dim; i++) {
		for (j = 0; j < y_dim; j++) {
			printf("%s	", point_maze[i][j]);
		}
		printf("\n");
	}


*/
  return 0;
}
