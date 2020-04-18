/** 
 *  @file simplematfctns.h
 *  @brief Provides simple math functions
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 15.04.2020  	First Implementation of:
 *						kumulativ_quadratic_sum			
 *	@date 18.04.2020    Changed kumulativ_quadratic_sum to return array
 * 
 *  @todo -
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.12
 */

#ifndef SIMPLEMATFCTNS_H
#define SIMPLEMATFCTNS_H
#include"../arrayhelpers/arrayhelpers.h"
/**
 * @fn double kumulativ_quadratic_sum(doublearr_t* arr);
 * @brief calculates the kumulativ quadtratic sum of the given array

 *
 * @param arr Array to calculate the quadtratic sum of
 *
 * @return Array with qudratic sums
 */
doublearr_t* kumulativ_quadratic_sum(doublearr_t* arr);
#endif //ifndef SIMPLEMATFCTNS_H
