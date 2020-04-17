/** 
 *  @file error_handler.h 
 *  @brief Provides functions,to handle errors
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 25.03.2020  	First Implementation of:
 *						zeta
 *						
 * 
 *  @todo change to using math.h
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1   
 */
#include <stdio.h>
#include <math.h>

#include "mypowers.h"
#include "myzeta.h"


double zeta(double s){
	
	double pres=PRES; //set precision
	double sum=1;//Summand
	double zeta_s=0;//final value
	
	//test rather zeta(s)<infty predefined
	if(s<=1){
		printf("Zeta(%lf) is inf!\n",s);
		return INFINITY;
	}
	
	//itterate until the added value is smaller than "pres"
	for(int k=1;sum>pres;k++){
		sum=1/power(k,s);
		zeta_s+=sum;
	}
	return zeta_s;
}