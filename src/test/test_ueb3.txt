#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../gauss_legendre_integration/gauss_legendre_integration.h"
#include "gsl/gsl_integration.h"
#include "../generalmemorymanager/generalmemorymanager.h"
#include "../specialfctns/specialfctns.h"

double f1(double x){
	return cos(log (x)/x)/x;
}
int k=42;
double f2(double z){
	return cos(z)/(z+k*(M_PI)+xlogofx_y_inv (z+k*(M_PI)));
}


int main(int argc, char *argv[]){
	//Part1:
	mem_init (0);
	int aofspoints=15;
	double upperbound=1.;
	double epsilon=1e-1;
	for(int i=0;i<5;i++){
		printf("Epsilon=%e\tResult=%e\n",epsilon,
					converge_integrate(f1,epsilon,upperbound,0.1,
							gausslegendre_integration));
		epsilon/=10.;
	}
	
	//Part2:
	double y=5.;
	double x=xlogofx_y_inv(y);
	printf ("x(%e)=%e\ty(x(y))=%e\n",y,x,x*log (x));
	k=0;
	double sigma_n=gausslegendre_integration(f2,0,M_PI_2,aofspoints);
	FILE* myfile=fopen ("data/ueb3_int2.txt", "w");
	fprintf(myfile,"%d;%.10e\n",k,sigma_n-0.323367431677778761399370087952170446651046625725469661681036443);
	for(k=1;k<1e6;k++){
		sigma_n+=pow(-1,k)*gausslegendre_integration(f2,-(M_PI_2),M_PI_2,
													 aofspoints);
		fprintf(myfile,"%d;%.10e\n",k,sigma_n-0.323367431677778761399370087952170446651046625725469661681036443);
	}
	fclose (myfile);
	mem_free_all ();
	
	//Part3:
	return EXIT_SUCCESS;
}
