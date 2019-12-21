#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int myrank =2, nproc = 4;
	printf("%d\n", &myrank);
	printf("%d", myrank);
	return 0;
}
