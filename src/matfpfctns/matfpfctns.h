/** 
 *  @file matfpfctns.h
 *  @brief Provides functions,to work with math function pointers
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 9.04.2020		valtable_double,integrate,integrate_cos,
 * 						convergeintegrate
 *  @date 21.04.2020	Added rootbisection,rootmodifiedsecant,rootsecant,
 * 						symthirdderivativeoptimized,symthirdderivative,
 * 						symsecondderivativeoptimized,symsecondderivative,
 * 						symfirstderivativeoptimized,symfirstderivative
 *  @date 22.04.2020	Renamed integrate->integratetrapez
 * 						Deleted integrate_cos
 * 						Refreshed convergeintegrate to generalform
 * 						Added integrate
 *  @todo cheack in valtable rather ferror gets set if the file does not exist
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.3  
 */
 
#ifndef MATFPFCTNS_H
#define MATFPFCTNS_H

/**
 * @fn int valtable_double(double (*fp)(double),char* filename,double step, double start, double end);
 * @brief Function to calculate a value table of a given function
 *
 * The given function ("fp") needs to have 1 dimensional In- and Output
 * And the Output table is saved in "filename"
 *
 * @param fp Function pointer to math fct
 * @param filename Name of file to write into, appends if it already exists
 * @param start Sets the value to start with
 * @param step Sets the value to inkrement by in each step
 * @param end Sets the value to end the table by
 * 
 * @return 1:Some Error, 0: No Error
 */
int valtable_double(double (*fp)(double),char* filename,double step, double start, double end);



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



/** @fn double integrate(double* weights,double* x_sampling_points,int n,
 * 						double (*fp)(double));
 * @brief Approximates the integral of "fp"
 * 
 * Approximates the integral of "fp" using the given weights and steps
 * 
 * @param weights	Array of the weights for the sampling points
 * @param x_sampling_points	Array of sampling points
 * @param n		Amount of sampling points
 * @param fp	Math function pointer to function to integrate
 */
double integrate(double* weights,double* x_sampling_points,int n,
				 double (*fp)(double));



/**
 * @fn double integratetrapez(double start, double end,double (*fp)(double), 
 * unsigned int n);
 * @brief approximates the integral of "fp" by trapezsum
 *
 * Approximates the integral of "fp" by trapezsum
 * over "n" subintervalls in ["start","end"]
 * The given function ("fp") needs to have 1 dimensional In- and Output
 *
 * @param start Start value of the integral
 * @param end End value of the integral
 * @param fp Math function pointer to function to integrate
 * @param n Amount of subintervalls in ["start","end"]
 * 
 * @return Value of the approximated integral
 */
double integratetrapez(double start,double end,double (*fp)(double),
					   unsigned int n);



/**
 * @fn double convergeintegrate(double start,double end,double (*fp)(double),
 * 		double precision,
 * 		double (*integrate_fp)(double,double,double(*fp)(double),unsigned int));
 * @brief approximates the integral of "fp" to the specifed "precision"
 *
 * Approximates the integral of "fp" using "integrate_fp"
 * and the specifed "precision"
 * The given function ("fp") needs to have 1 dimensional In- and Output.
 * 
 * @param start Start value of the integral
 * @param end End value of the integral
 * @param fp Math function pointer to function to integrate
 * @param precision Difference between different subintervall trys
 * @param integrate_fp Function to use to integrate
 * 
 * @return Value of the approximated integral
 */
double convergeintegrate(double start,double end,double (*fp)(double),
		double precision,
		double (*integrate_fp)(double,double,double(*fp)(double),unsigned int));


#endif //ifndef MATFPFCTNS_H
