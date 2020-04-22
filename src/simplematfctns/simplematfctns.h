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
 * @return Array with quadratic sums
 */
doublearr_t* kumulativ_quadratic_sum(doublearr_t* arr);



/**
 * @fn double gammafunction(double z,double precision);
 * @brief calculates the gamma function at z with the given precision
 *
 * @param z Point of interest
 * @param precision Needed precision
 *
 * @return gamma(z)
 */
double gammafunction(double z,double precision);



/**
 * @fn double gammahelp(double* variables);
 * @brief Helpfunction needed for gammafunction
 *
 * @param variables Array of the variables
 *
 * @return exp(-variables[0])*pow(variables[0],variables[1]-1)
 */
double gammahelp(double* variables);
#endif //ifndef SIMPLEMATFCTNS_H
