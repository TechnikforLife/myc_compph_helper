/** 
 *  @file strswitchchar.c
 *  @brief Provides functions,to execute char/string operations
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 14.04.2020  	First Implementation of:
 *						strswch
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
#include <strswitchchar.h>
#include <stdio.h>

void strswch(char str[],int n, char chold, char chnew){
	//iterrate through str and swap chold for chnew
	for(int i=0;i<n;i++){
		if(str[i]==chold){
			str[i]=chnew;
		}
		
	}
}