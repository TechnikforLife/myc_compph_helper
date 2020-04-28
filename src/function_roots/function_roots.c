#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "function_roots.h"
#include "../derivatives/derivatives.h"

double rootsecant(double a,double b,double (*fp)(double),double precision){
	/**
	 * Declarations:
	 * 
	 * @var x_i 	Current x
	 * @var x_im1	Prev x
	 * @var x_ip1	Next x
	 * @var i		Itteration variable
	 * 
	 */
	double x_i=a;
	double x_im1=b;
	double x_ip1=b+1;
	int i;
	
	/**
	 * @note	Try to estimate the root of "fp" with the given startvalues
	 * 			and to the given precision.
	 */
	for(i=0;i<10000;i++){
		x_ip1=x_i+(fp(x_i)*(x_im1-x_i))/(fp(x_i)-fp(x_im1));
		if(fabs(x_ip1-x_i)<precision){
			break;
		}
		x_im1=x_i;
		x_i=x_ip1;
	}
	if(i==10000){
		printf("[WARNING] Could not reach given precision!\n");
	}
	return x_ip1;
}

double rootmodifiedsecant(double start,double (*fp)(double),double precision){
	/**
	 * Declarations:
	 * 
	 * @var x_i 	Current x
	 * @var x_ip1	Next x
	 * @var i		Itteration variable
	 * 
	 */
	double x_i=start;
	double x_ip1;
	int i;
	
	/**
	 * @note	Try to estimate the root of "fp" with the given startvalue
	 * 			and to the given precision.
	 */
	for(i=0;i<10000;i++){
		x_ip1=x_i-fp(x_i)/symfirstderivativeoptimized(x_i, fp);
		if(fabs(x_ip1-x_i)<precision){
			break;
		}
		x_i=x_ip1;
	}
	if(i==10000){
		printf("[WARNING] Could not reach given precision!\n");
	}
	return x_ip1;
}



double rootbisection(double start,double end, double(*fp)(double),
					 double precision){
	/**
	 * Declarations:
	 * 
	 * @var upper 		Upper bound
	 * @var lower		Lower bound
	 * @var next		Next bound
	 * @var fpofupper	fp(upper)
	 * @var fpoflower	fp(lower)
	 * @var fpofnext	fp(next)
	 * @var i			Itteration variable
	 */
	double upper=end;
	double lower=start;
	double next;
	double fpofupper=fp(upper);
	double fpoflower=fp(lower);
	double fpofnext;
	int i;
	/**
	 * @note 	Check rather there could be only 1 root in the intervall
	 * 			and rather a boundary is already the root.
	 */
	if(fpofupper*fpoflower>0){
		printf("[ERROR] Could not find root in intervall:"
					" [%e,%e]!\n",start,end);
		exit(1);
	}
	if(fpofupper==0){
		return upper;
	}
	if(fpoflower==0){
		return lower;
	}
	
	/**
	 * @note In each step: 	Calculate the next possible boundary.
	 * 						Check in which subinterval the root is and 
	 * 						set it to be the new intervall.
	 * Stop if the Itteration limit or precision is reached.
	 */
	for(i=0;i<10000;i++){
		next=(lower+upper)/2;
		fpofnext=fp(next);
		if(fpofnext==0){
			return next;
		}
		if(fpofupper*fpofnext<0){
			lower=next;
			fpoflower=fp(lower);
		}else if(fpoflower*fpofnext<0){
			upper=next;
			fpofupper=fp(upper);
		}else{
			fprintf(stderr,"Sign error: No sign change found!\n");
			return next;
		}
		if(fabs(upper-lower)<precision){
			break;
		}
	}
	
	if(i==10000){
		printf("[WARNING] Could not reach given precision!\n");
	}
	return next;
}