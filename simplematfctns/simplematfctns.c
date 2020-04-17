/** 
 *  @file simplematfctns.c 
 *  @brief Provides simple math functions
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 15.04.2020  	First Implementation of:
 *						kumulativ_quadratic_sum			
 *						
 * 
 *  @todo -
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1   
 */
#include "simplematfctns.h"

double kumulativ_quadratic_sum(doublearr_t* arr){
	double sum;//value of the sum
	int i;//itterration variable
	
	//calculate the sum
	for(i=0;i<arr->length;i++){
		sum+=arr->dataptr[i];
	}
	
	//return the sum
	return sum;
}