/** 
 *  @file numerov.h 
 *  @brief Provides functions for numerov
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 24.05.2020  	First Implementation of:
 *						
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1   
 */
#ifndef NUMEROV_H
#define NUMEROV_H
typedef struct numerovdata{
	double* r;
	double* g;
	double* s;
	double  h;
	int  n;
}numerov_data_t;
void init_ittertable(double start,double end,numerov_data_t* dat,
					double(*fg)(double),double(*fs)(double));

void numerovup(numerov_data_t dat,int steps,double y0,double y1,double *y);

void numerovdown(double *r,double *g,double *s,double h,int n,int steps,
				 double yn, double ynm1,double *y);

#endif //ifndef NUMEROV_H