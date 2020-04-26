#include "gauss_legendre_integration.h"
#include <gsl/gsl_integration.h>
#include <stdio.h>
#include <stdlib.h>
#include "../error_handler/error_handler.h"
#include "../generalmemorymanager/generalmemorymanager.h"
#include "../matfpfctns/matfpfctns.h"

double gausslegendre_integration(double (*func)(double),
						double lowerbound, double upperbound,int n){
	/**
	 * Declarations:
	 * 
	 * @var gsl_integration_glfixed_table 		Pointer to the w,x table
	 * @var i				itterration variable
	 * @var check			check value, if sth went wrong in gsl
	 * @var xilist			Pointer to x list
	 * @var wilist			Pointer to w list
	 * @var integralapprox	approximated value of the integral
	 */
	gsl_integration_glfixed_table* xwtable_mem;
	size_t i=0;
	int check=0;
	double* xilist,*wilist;
	double integralapprox;
	
	/**
	 * @note Memory allocation
	 */
	xilist=mem_alloc(n*sizeof(double));
	wilist=mem_alloc(n*sizeof(double));
	xwtable_mem=gsl_integration_glfixed_table_alloc(n);
	fatal_error(xwtable_mem==NULL,"GSL mem allocation failed\n",1,__func__,
				__FILE__,__LINE__);
	
	/**
	 * @note Retrievel of the sampling points an their weights
	 */
	for(i=0;i<n&&check==0;i++){
		check=gsl_integration_glfixed_point (lowerbound, upperbound, i, 
									   xilist+i, wilist+i, xwtable_mem);
	}
	fatal_error(i!=n,"GSL retrievel of fixed points failed\n",1,__func__,
				__FILE__,__LINE__);
	gsl_integration_glfixed_table_free (xwtable_mem);
	
	/**
	 * @note Calculate the approximation of the integral
	 */
	integralapprox = integrate(wilist,xilist,n,func);
	mem_free (wilist);
	mem_free (xilist);
	return integralapprox;
}
