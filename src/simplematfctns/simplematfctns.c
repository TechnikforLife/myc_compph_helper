#include "simplematfctns.h"
#include "../generalmemorymanager/generalmemorymanager.h"
#include "../integrate_trapez/integrate_trapez.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
doublearr_t* kumulativ_quadratic_sum(doublearr_t* arr){
	/**
	 * Declarations:
	 * sum	array of the sums
	 * i	itterration variable
	 */
	doublearr_t* sum;
	int i;
	sum=mem_alloc(sizeof (doublearr_t));
	sum->dataptr=mem_alloc (sizeof(double)*arr->length);
	
	/**
	 * @note	Calculate the quadratic sum till each element
	 */
	sum->dataptr[0]=arr->dataptr[0]*arr->dataptr[0];
	for(i=1;i<arr->length;i++){
		sum->dataptr[i]=sum->dataptr[i-1]+arr->dataptr[i]*arr->dataptr[i];
	}
	return sum;
}


double gammafunction(double z,double precision){
	/**
	 * Declarations:
	 * variables	Pointer to the arrays of variables
	 * ret			Return value
	 */
	double* variables;
	double ret=1;
	
	/**
	 * @note Use the properties of the gamma function,to eas up the calculation
	 * 		 Afterwards "variables" gets set and  
	 */
	
	while(z>3){
		z-=1;
		ret*=z;
	}
	while(z<2){
		ret/=z;
		z+=1;
	}
	variables=(double*)mem_alloc (sizeof (double)*2);
	variables[1]=z;
	ret*=convergeintegrate_homogenstepcount(0,10,gammahelp,precision,0,1,variables);
	mem_free(variables);
	return ret;
}

double gammahelp(double* variables){
	return exp(-variables[0])*pow(variables[0],variables[1]-1);
}

