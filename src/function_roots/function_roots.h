/** 
 *  @file function_roots.h
 *  @brief Provides functions,to calculate roots
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 28.04.20	Reorganisation of functions from matfpfctns 
 * 					to function_roots
 *  @date 23.05.20	Added division by zero prevention
 * 
 *  @todo -
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 1.2 
 */

#ifndef FUNCTION_ROOTS_H
#define FUNCTION_ROOTS_H

/**
 * @fn double rootsecant(double a,double b,double (*fp)(double),
 * 						double precision);
 * @brief Approximates the root of "fp" using the classical secant method
 *
 * Approximates the root of "fp"(must not be the nearest root!)
 * using the classical secant method
 * with the start values "a" and "b".
 *
 * @param a First start value
 * @param b Second start value
 * @param fp Math function pointer to function to use
 * @param precision Precision to which the root should be determined
 * 
 * @return Approximation of the root of "fp"
 */
double rootsecant(double a,double b,double (*fp)(double),double precision);



/**
 * @fn double rootmodifiedsecant(double start,double (*fp)(double),
 * 								double precision);
 * @brief Approximates the root of "fp" using the modified secant method
 *
 * Approximates the nearest root of "fp"
 * using the modified secant method
 * with the start value "start".
 *
 * @param start Start value
 * @param fp Math function pointer to function to use
 * @param precision Precision to which the root should be determined
 * 
 * @return Approximation of the root of "fp"
 */
double rootmodifiedsecant(double start,double (*fp)(double),double precision);



/**
 * @fn double rootbisection(double start,double end, double(*fp)(double),
 * 							double precision);
 * @brief Approximates the root of "fp" using the bisection method
 *
 * Approximates the root in the intervall ["start","end"] of "fp"
 * using the bisection method.
 *
 * @param start Start value of the intervall
 * @param end End value of the intervall
 * @param fp Math function pointer to function to use
 * @param precision Precision to which the root should be determined
 * 
 * @return Approximation of the root of "fp"
 */
double rootbisection(double start,double end, double(*fp)(double),
					 double precision);

#endif //ifndef FUNCTION_ROOTS_H