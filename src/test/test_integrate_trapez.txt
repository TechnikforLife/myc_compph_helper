#include "../integrate_trapez/integrate_trapez.h"
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

double f2(double* variables){
	return pow(variables[0],-3);
}


int main (int argc, char *argv[]){
	double xvar[1];
	printf("%e?=%e\n",0.5,convergeintegrate_homogenstepcount (1,10,f2, 1e-4,0,1,xvar) );
	return EXIT_SUCCESS;
}
