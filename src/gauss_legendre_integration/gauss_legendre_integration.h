/** 
 *  @file gauss_legendre_integration.h 
 *  @brief Provides functions,to integrate using gauss legendre
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 26.04.2020 	First Implementation of: gausslegendre_integration
 * 
 *  @todo performance improvement
 * 
 *  @test 
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1
 */
#ifndef GAUSS_LEGENDRE_INTEGRATION_H
#define GAUSS_LEGENDRE_INTEGRATION_H
/**
 * @fn double gausslegendre_integration(double (*func)(double),
 * 						double lowerbound, double upperbound,int n);
 * @brief Integrates the given function from "lowerbound" to "upperbound"
 *
 * Integrates the given function from "lowerbound" to "upperbound" using
 * gauss-legendre.
 * An Approximation of the given integral is returned.
 * If "func" is a polynom of degree < 2n-1, the returned value is exact
 *
 * @param func Pointer to the function to integrate
 * @param lowerbound Lower bound of the integral
 * @param upperbound Upper bound of the integral
 * @param n Amount of sampling points
 *
 * @return Approximation of the given integral 
 */
double gausslegendre_integration(double (*func)(double),
						double lowerbound, double upperbound,int n);

/**
 * @fn double converge_integrate(double (*func)(double), double lowerbound, 
 * 						  double upperbound,double relprecision,
 * 						  double (*method)(double (*fp)(double),double lb,
 * 						  double ub,int n));
 * @brief Integrates the given function from "lowerbound" to "upperbound"
 *
 * Integrates the given function from "lowerbound" to "upperbound" using
 * the given "method".
 * An Approximation of the given integral is returned.
 *
 * @param func Pointer to the function to integrate
 * @param lowerbound Lower bound of the integral
 * @param upperbound Upper bound of the integral
 * @param relprecision Required precision of the approximation
 * @param method Method to use to integrate 
 *
 * @return Approximation of the given integral 
 */
double converge_integrate(double (*func)(double), double lowerbound, 
						  double upperbound,double relprecision,
						  double (*method)(double (*fp)(double),double lb,
						  double ub,int n));
#endif // GAUSS_LEGENDRE_INTEGRATION_H
