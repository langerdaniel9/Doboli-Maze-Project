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

// 17 main functions, will move to main17.h/main17.c file later
void MARK();

void MOVE_F();

void MOVE_B();

void MOVE_L();

void MOVE_R();

int CWL();

int CWR();

int CWF();

int CWB();

void PUSH();

void POP();

coord PEEK();

void CLEAR();

void BACKTRACK();

void BJPI();

void CJPI();

void RP(int n, int t);

//--------------------------------
// Other functions, will move to functions.h/functions.c file later

void findDims();

void createArrays();

void scan();

void findStart();

void checkSurroundings();

void logic();

void reviewPriorities();

void checkIfOnDeed();

void printMaze();

void printDeed();

void printPheromone();
//--------------------------------