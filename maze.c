#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *maze; 
	
	if ((maze = fopen("maze.txt", "r")) == NULL) {
		printf("error in opening maze.txt");
		exit(1);
	} 

	int i;
	int starting_x, starting_y;
	int x_dim, y_dim;
	
	fscanf(maze, "(%i, %i)", &starting_x, &starting_y);
	fscanf(maze, "%i %i", &x_dim, &y_dim);
	
	printf("(%i, %i)\n%i %i", starting_x, starting_y, x_dim, y_dim);
	



  return 0;
}
