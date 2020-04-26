#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../gauss_legendre_integration/gauss_legendre_integration.h"
#include "gsl/gsl_integration.h"
#include "../generalmemorymanager/generalmemorymanager.h"

double f1(double x){
	return cos(log (x)/x)/x;
}



int main(int argc, char *argv[]){
	mem_init (0);
	double upperbound=1.;
	double epsilon=1e-1;
	for(int n=2;n<50;n++){
		epsilon=1e-1;
		for(int i=0;i<20;i++){
			printf("Epsilon=%e\tResult=%e\n",epsilon,
			   gausslegendre_integration(cos,epsilon,upperbound,n));
			epsilon/=10.;
		}
		printf("\n");
	}
	
	mem_free_all ();
	return EXIT_SUCCESS;
}
