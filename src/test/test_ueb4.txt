#include "../integrate_trapez/integrate_trapez.h"
#include <stdio.h>
#include <stdlib.h>
#include "../generalmemorymanager/generalmemorymanager.h"
#include <math.h>
#include <sys/time.h>

double f1(double* variables,int dim){
	double ret=1.;
	for(int i=0;i<dim;i++){
		ret*=variables[i];
	}
	return ret;
}
double f2(double* variables,int dim){
	double ret=1.;
	for(int i=0;i<dim;i++){
		ret*=variables[i];
	}
	return pow(ret,1./(double)dim);
}


int main (int argc, char *argv[]){
	mem_init (0);
	int dim=3;
	struct timeval ta, te;
	long int seconds;
	long int useconds;
	double sectotal;
	double x;
	FILE* stream=fopen("data/ueb4_3.dat","w");
	for(int n=1;n<=300;n*=2){
		gettimeofday ( &ta, (struct timezone *)NULL );
		x=integrate_trapez_hd_cube(dim,0,1,n,f2);
		gettimeofday ( &te, (struct timezone *)NULL );
	
		seconds = te.tv_sec - ta.tv_sec;
		useconds = te.tv_usec - ta.tv_usec;
		sectotal=(double)seconds+1e-6*(double)useconds;
		fprintf ( stream, "%d;%e\n",n,sectotal);
		fprintf ( stdout, "%d;%e\n",n,sectotal);
		
	}
	
	fprintf ( stdout, "time for Integrationsroutine = %ld sec %ld usec\n",
		seconds, useconds );
	
	double exact=pow (((double)dim)/((double)dim+1), dim);
	printf("Value=%.10e\tExact%.10e\tDiff%.10e\n",x,exact,(exact-x)/exact );
	fclose (stream);
	mem_free_all ();
	
	return EXIT_SUCCESS;
}
/*
 * time for Integrationsroutine = 0 sec 131553 usec
 * Value=4.2087217239e-01	Exact4.2187500000e-01	Diff2.3770728596e-03
 */
