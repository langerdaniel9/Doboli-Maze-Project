#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *maze; 
	
	if ((maze = fopen("maze.txt", "r")) == NULL) {
		printf("error in opening maze.txt");
		exit(1);
	} 

	int i, j;
	int starting_x, starting_y;
	int x_dim, y_dim;
	
	fscanf(maze, "(%i, %i)", &starting_x, &starting_y);
	fscanf(maze, "%i %i", &x_dim, &y_dim);
	
	printf("(%i, %i)\n%i %i", starting_x, starting_y, x_dim, y_dim);
	
	char actual_maze[(x_dim) * (y_dim)];
//	char* actual_maze;
//	printf("%i %i\n", x_dim, y_dim);
	char *point_maze[(x_dim) * (y_dim)];
	point_maze[(x_dim) * (y_dim)] = &actual_maze[(x_dim) * (y_dim)];
	*point_maze = (char*) malloc (((x_dim) * (y_dim)) * sizeof(char));

//	actual_maze[22] = '*';
//	printf("\n%c", actual_maze[22]);
	
	printf("\nmaze = %i, char = %i", sizeof(actual_maze), sizeof(char));
	
//	char actual_maze[0][0];
//	
//	for (i = 0; i < x_dim; i++) {
//		for (j = 0; j < y_dim; j++) {
//			actual_maze = (char*) malloc (y_dim * sizeof(char));
//		}
//		actual_maze = (char*) malloc (x_dim * sizeof(char));
//	}


  return 0;
}
