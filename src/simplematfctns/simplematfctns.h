/** 
 *  @file simplematfctns.h
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

#ifndef SIMPLEMATFCTNS_H
#define SIMPLEMATFCTNS_H
#include"../arrayhelpers/arrayhelpers.h"
/**
 * @fn double kumulativ_quadratic_sum(doublearr_t* arr);
 * @brief calculates the kumulativ quadtratic sum of the given array

 *
 * @param arr1 Pointer to integer array to search for
 *
 * @return Starting position of "arr1" in arr" or -1
 */
double kumulativ_quadratic_sum(doublearr_t* arr);
#endif //ifndef SIMPLEMATFCTNS_H