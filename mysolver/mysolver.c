/** 
 *  @file mysolver.c
 *  @brief Provides functions to solve equations
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 30.03.2020  	First Implementation of:
 *						squaresolv
 * 
 *  @todo Implement other functions (complex)
 * 
 *  @todo Implement own type for return objects
 *
 *  @test test complex functionality
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1   
 */
#include <stdio.h>
#include <math.h>
#include "mysolver.h"

//1: 1 Solution
//2: 2 Solutions
//0: No Solutions
//-1: INF Solutions

int squaresolv(double* abc,double* sol){
	double insqrt //saves value in sqrt
	
	//test rather some special cases are met
	if(abc[0]==0){//a=0
		if(abc[1]!=0){//b!=0&a=0
			sol[0]=-abc[2]/abc[1];
			return 1;
		}else if(abc[2]!=0){//b=0&a=0&c!=0
			return 0;
		}else{//b=0&a=0&c=0
			return -1;
		}
	}
	
	//test rather a value is very close to 0
	for(int i=0;i<3;++i){
		if(fabs(abc[i])<PRES){
			printf("Warning: abc_%d=%f ,did you mean: abc_%d=0?\n",i+1,abc[i],i+1);
		}
	}
	
	//a!=0:
	insqrt=(abc[1]*abc[1])/(abc[0]*abc[0]*4.)-abc[2]/abc[0];
	
	//test rather complex computation is needed
	if(insqrt<0){
		printf("Complex calculation not supported by squaresolv use csquaresolv!\n");
		return -1;
	}
	
	//test rather the solutions are the same
	if(insqrt==0){//both sol are the same
		sol[0]=-abc[1]/(2*abc[0]);
		return 1;
	}
	
	//or very close to being the same
	if(insqrt<PRES){
		printf("Warning: the solutions might be the same!\n");
	}
	
	//save the solutions
	sol[0]=-abc[1]/(2*abc[0])+sqrt(insqrt);
	sol[1]=-abc[1]/(2*abc[0])-sqrt(insqrt);
	return 2;
}

