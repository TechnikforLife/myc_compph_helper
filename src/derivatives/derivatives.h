/** 
 *  @file derivatives.h
 *  @brief Provides functions,to calculate derivatives
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 28.04.20	Reorganisation of functions from matfpfctns to derivatives
 * 
 *  @todo -
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1 
 */

#ifndef DERIVATIVES_H
#define DERIVATIVES_H

/**
 * @fn double symfirstderivative(double x,double h,double (*fp)(double));
 * @brief Approximates the first derivative of the function "fp" at "x"
 *
 * Approximates the first derivative of "fp" at "x" using Taylor-formula 
 * (till order of h²) of f(x+h) and f(x-h).
 *
 * @param x Point of interest
 * @param h Step size 
 * @param fp Math function pointer to function to derive
 * 
 * @return Approximation of the first derivative of "fp" at "x"
 */
double symfirstderivative(double x,double h,double (*fp)(double));



/**
 * @fn double symfirstderivativeoptimized(double x,double (*fp)(double));
 * @brief Approximates the first derivative of the function "fp" at "x"
 *
 * Approximates the first derivative of "fp" at "x" using Taylor-formula 
 * of f(x+h) and f(x-h).
 * h was chosen to optimize preciscion.
 *
 * @param x Point of interest
 * @param fp Math function pointer to function to derive
 * 
 * @return Approximation of the first derivative of "fp" at "x"
 */
double symfirstderivativeoptimized(double x,double (*fp)(double));



/**
 * @fn double symsecondderivative(double x,double h,double (*fp)(double));
 * @brief Approximates the second derivative of the function "fp" at "x"
 *
 * Approximates the second derivative of "fp" at "x" using Taylor-formula 
 * (till order of h³) of f(x+h),f(x) and f(x-h).
 *
 * @param x Point of interest
 * @param h Step size 
 * @param fp Math function pointer to function to derive
 * 
 * @return Approximation of the second derivative of "fp" at "x"
 */
double symsecondderivative(double x,double h,double (*fp)(double));



/**
 * @fn double symsecondderivativeoptimized(double x,double (*fp)(double));
 * @brief Approximates the second derivative of the function "fp" at "x"
 *
 * Approximates the second derivative of "fp" at "x" using Taylor-formula 
 * of f(x+h),f(x) and f(x-h).
 * h was chosen to optimize preciscion.
 *
 * @param x Point of interest
 * @param fp Math function pointer to function to derive
 * 
 * @return Approximation of the second derivative of "fp" at "x"
 */
double symsecondderivativeoptimized(double x,double (*fp)(double));



/**
 * @fn double symsecondderivative(double x,double h,double (*fp)(double));
 * @brief Approximates the third derivative of the function "fp" at "x"
 *
 * Approximates the third derivative of "fp" at "x" using Taylor-formula 
 * (till order of h³) of f(x+2h),f(x+h),f(x),f(x-h) and f(x-2h).
 *
 * @param x Point of interest
 * @param h Step size 
 * @param fp Math function pointer to function to derive
 * 
 * @return Approximation of the third derivative of "fp" at "x"
 */
double symthirdderivative(double x,double h,double (*fp)(double));



/**
 * @fn double symthirdderivativeoptimized(double x,double (*fp)(double));
 * @brief Approximates the third derivative of the function "fp" at "x"
 *
 * Approximates the third derivative of "fp" at "x" using Taylor-formula 
 * of f(x+2h),f(x+h),f(x),f(x-h) and f(x-2h).
 * h was chosen to optimize preciscion.
 *
 * @param x Point of interest
 * @param fp Math function pointer to function to derive
 * 
 * @return Approximation of the third derivative of "fp" at "x"
 */
double symthirdderivativeoptimized(double x,double (*fp)(double));

#endif //ifndef DERIVATIVES_H