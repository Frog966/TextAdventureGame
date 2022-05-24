#include<time.h>
#include <stdlib.h> 

// Please call srand() first!

// Returns a number in the range between min and max - 1
int intRand(int max = RAND_MAX, int min = 0) {
	return rand() % max + min;
}