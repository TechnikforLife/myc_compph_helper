#include <stdio.h>
#include <stdlib.h>
#include "specialfctns.h"
#include <math.h>
double xlogofx_y_inv(double y){
	
	double x_n;
	double x_np1;
	if(y<0){
		fprintf(stderr,"Negativ y not officially supported in xlogofx_y_inv\n");
	}
	if(y>10){
		x_np1=y/log(y)*pow (1-log (log(y))/(1+log(y)),-1);
	}else{
		x_np1=1.0125+0.8577*y-0.129013*y*y+0.0208645*pow (y, 3)
			-0.00176148*pow(y,4)+0.000057941*pow(y,5);
	}
	do{
		x_n=x_np1;
		x_np1=(x_n+y)/(log (x_n)+1);
	}while(fabs(x_n-x_np1)>x_n*1e-15);
	return x_np1;
}