#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/// 17 - Functions File ///

// Project Members: Daniel Langer, Alan George, and Kenneth Procacci //

void MARK()
{
	if (left + right + up + down > 1)
	{
		PUSH();
		pheromoneArray[currentPos.x + currentPos.y * x_dim] = 1;
		fprintf(output, "MARK\t\tMarked spot (%i, %i)\n", currentPos.x, currentPos.y);
	}
	else if (left + right + up + down == 0)
	{
		pheromoneArray[currentPos.x + currentPos.y * x_dim] = 1;
		fprintf(output, "MARK\t\tMarked spot (%i, %i)\n", currentPos.x, currentPos.y);
		BACKTRACK();
	}
	else
	{
		pheromoneArray[currentPos.x + currentPos.y * x_dim] = 1;
		fprintf(output, "MARK\t\tMarked spot (%i, %i)\n", currentPos.x, currentPos.y);
	}
}

void MOVE_F()
{
	if (steps >= MAX_NUMBER_OF_STEPS)
	{
		finished();
	}
	// Move up one spot (↑) and mark previous square
	if (!up || moved)
	{
		return;
	}
	else
	{
		currentPos.y -= 1;
		steps++;
		fprintf(output, "MOVE_F\t\tMoved up to (%i, %i) | Step Count = %i\n", currentPos.x, currentPos.y, steps);
		moved = true;
		checkIfOnDeed();
	}
}

void MOVE_B()
{
	if (steps >= MAX_NUMBER_OF_STEPS)
	{
		finished();
	}
	// Move down one spot (↓) and mark previous square
	if (!down || moved)
	{
		return;
	}
	else
	{
		currentPos.y += 1;
		steps++;
		fprintf(output, "MOVE_B\t\tMoved down to (%i, %i) | Step Count = %i\n", currentPos.x, currentPos.y, steps);
		moved = true;
		checkIfOnDeed();
	}
}

void MOVE_L()
{
	if (steps >= MAX_NUMBER_OF_STEPS)
	{
		finished();
	}
	// Move left one spot (←) and mark previous square
	if (!left || moved)
	{
		return;
	}
	else
	{
		currentPos.x -= 1;
		steps++;
		fprintf(output, "MOVE_L\t\tMoved left to (%i, %i) | Step Count = %i\n", currentPos.x, currentPos.y, steps);
		moved = true;
		checkIfOnDeed();
	}
}

void MOVE_R()
{
	if (steps >= MAX_NUMBER_OF_STEPS)
	{
		finished();
	}
	// Move right one spot (→) and mark previous square
	if (!right || moved)
	{
		return;
	}
	else
	{
		currentPos.x += 1;
		steps++;
		fprintf(output, "MOVE_R\t\tMoved right to (%i, %i) | Step Count = %i\n", currentPos.x, currentPos.y, steps);
		moved = true;
		checkIfOnDeed();
	}
}

int CWL() // check left
{
	moved = false;
	if (mazeArray[(currentPos.x + (currentPos.y * x_dim)) - 1] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) - 1] == 0)
	{
		fprintf(output, "CWL\t\tLeft of (%i, %i) is empty\n", currentPos.x, currentPos.y);
		left = 1;
		return 1;
	}
	fprintf(output, "CWL\t\tLeft of (%i, %i) is occupied\n", currentPos.x, currentPos.y);
	left = 0;
	return 0;
}

int CWR() // check right
{
	moved = false;
	if (mazeArray[(currentPos.x + (currentPos.y * x_dim)) + 1] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) + 1] == 0)
	{
		fprintf(output, "CWR\t\tRight of (%i, %i) is empty\n", currentPos.x, currentPos.y);
		right = 1;
		return 1;
	}
	fprintf(output, "CWR\t\tRight of (%i, %i) is occupied\n", currentPos.x, currentPos.y);
	right = 0;
	return 0;
}

int CWF() // check up
{
	moved = false;
	if (mazeArray[(currentPos.x + (currentPos.y * x_dim)) - x_dim] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) - x_dim] == 0)
	{
		fprintf(output, "CWF\t\tUp of (%i, %i) is empty\n", currentPos.x, currentPos.y);
		up = 1;
		return 1;
	}
	fprintf(output, "CWF\t\tUp of (%i, %i) is occupied\n", currentPos.x, currentPos.y);
	up = 0;
	return 0;
}

int CWB() // check down
{
	moved = false;
	if (mazeArray[(currentPos.x + (currentPos.y * x_dim)) + x_dim] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) + x_dim] == 0)
	{
		fprintf(output, "CWB\t\tDown of (%i, %i) is empty\n", currentPos.x, currentPos.y);
		down = 1;
		return 1;
	}
	fprintf(output, "CWB\t\tDown of (%i, %i) is occupied\n", currentPos.x, currentPos.y);
	down = 0;
	return 0;
}

void PUSH()
{
	// If stack is full, clear it and continue adding the value
	if (stackPosition == MAX_SIZE)
	{
		CLEAR();
	}
	// Add a value to the top of the stack
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
	// Remove the element at the top of the stack
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
	// Return the value at the top of the stack
	int i;
	fprintf(output, "\tPEEK Peeked (%i, %i) from top of stack\n", stack[stackPosition - 1].x, stack[stackPosition - 1].y);
	return stack[stackPosition - 1];
}

void CLEAR()
{
	// Remove all elements currently stored in the stack
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
	if (steps >= MAX_NUMBER_OF_STEPS)
	{
		finished();
	}
	// Only gets called if there are no more immediate possible moves, so if there is nothing stored in the stack then there are no moves left at all
	if (stackPosition == 0)
	{
		finished();
	}
	steps++;
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
		MARK();
		// i represents the number of spaces jumped over, or the number of consecutive CW functions used
		int i = 1;

		while (mazeArray[(currentPos.x + (currentPos.y * x_dim)) - i] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) - i] == 0)
		{
			i++;
		}
		currentPos.y -= i;
		checkIfOnDeed();
		steps++;

		return;
	}
	else if (CWR() == 1)
	{
		MARK();
		int i = 1;
		while (mazeArray[(currentPos.x + (currentPos.y * x_dim)) + i] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) + i] == 0)
		{
			i++;
		}
		currentPos.y += i;
		checkIfOnDeed();
		steps++;

		return;
	}
	else if (CWF() == 1)
	{
		MARK();
		int i = 1;
		while (mazeArray[(currentPos.x + (currentPos.y * x_dim)) - (x_dim * i)] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) - (x_dim * i)] == 0)
		{
			i++;
		}
		currentPos.x += i;
		checkIfOnDeed();
		steps++;

		return;
	}
	else if (CWB() == 1)
	{
		MARK();
		int i = 1;
		while (mazeArray[(currentPos.x + (currentPos.y * x_dim)) + (x_dim * i)] == ' ' && pheromoneArray[(currentPos.x + (currentPos.y * x_dim)) + (x_dim * i)] == 0)
		{
			i++;
		}
		currentPos.x -= i;
		checkIfOnDeed();
		steps++;

		return;
	}

	fprintf(output, "BJPI ()\n");
}

void CJPI()
{
	if (left == 1)
	{
		MOVE_L;
	}
	else if (right == 1)
	{
		MOVE_R;
	}
	else if (up == 1)
	{
		MOVE_F;
	}
	else if (down == 1)
	{
		MOVE_B;
	}
}

void RP(char RParray[20][20], int t)
{
	// find the number of actions in the RP array
	int numActions = 0;
	while (strlen(RParray[numActions]) != 0)
	{
		numActions++;
	}

	// Repeat all of the actions in RP array t times
	int repetition = 0;
	for (repetition = 0; repetition < t; repetition++)
	{
		bool moved = false;
		int position = 0;
		for (position = 0; position <= numActions; position++)
		{
			if (strcmp(RParray[position], "CWL") == 0)
			{
				CWL();
			}
			else if (strcmp(RParray[position], "CWR") == 0)
			{
				CWR();
			}
			else if (strcmp(RParray[position], "CWF") == 0)
			{
				CWF();
			}
			else if (strcmp(RParray[position], "CWB") == 0)
			{
				CWB();
			}
			else if (strcmp(RParray[position], "MARK") == 0)
			{
				MARK();
			}
			else if (strcmp(RParray[position], "MOVE_F") == 0)
			{

				MOVE_F();
			}
			else if (strcmp(RParray[position], "MOVE_B") == 0)
			{

				MOVE_B();
			}
			else if (strcmp(RParray[position], "MOVE_L") == 0)
			{
				MOVE_L();
			}
			else if (strcmp(RParray[position], "MOVE_R") == 0)
			{
				MOVE_R();
			}
			else if (strcmp(RParray[position], "PUSH") == 0)
			{
				PUSH();
			}
			else if (strcmp(RParray[position], "POP") == 0)
			{
				POP();
			}
			else if (strcmp(RParray[position], "CLEAR") == 0)
			{
				CLEAR();
			}
			else if (strcmp(RParray[position], "PEEK") == 0)
			{
				PEEK();
			}
			else if (strcmp(RParray[position], "CJPI") == 0)
			{
				CJPI();
			}
			else if (strcmp(RParray[position], "BJPI") == 0)
			{
				BJPI();
			}
			else if (strcmp(RParray[position], "BACKTRACK") == 0)
			{
				BACKTRACK();
			}
		}
	}
}
