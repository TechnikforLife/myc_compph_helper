/** 
 *  @file integrate_trapez.h
 *  @brief Provides functions,to integrate functions
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 28.04.20	Reorganisation of functions from matfpfctns 
 * 					to integrate_trapez
 * 
 *  @todo -
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1 
 */

#ifndef INTEGRATE_TRAPEZ_H
#define INTEGRATE_TRAPEZ_H
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
 * @param variables Array of the variables
 * 
 * @return Value of the approximated integral
 */
double integratetrapez(double start,double end,double (*fp)(double*),
					   unsigned int n,double* variables);



/**
 * @fn double convergeintegrate_homogenstepcount(double start,double end,
 * 				double (*fp)(double),double precision,const int startisminfty,
 * 				const int endisinfty);
 * @brief approximates the integral of "fp" to the specifed "precision"
 *
 * Approximates the integral of "fp" using "integratetrapez"
 * and the specifed "precision"
 * The given function ("fp") needs to have 1 dimensional In- and Output.
 * 
 * @param start Start value of the integral
 * @param end End value of the integral
 * @param fp Math function pointer to function to integrate
 * @param precision Relative precision
 * @param integrate_fp Function to use to integrate
 * @param startisminfty Say rather the start is -infty
 * @param endisinfty Say rather the end is infty
 * @param variables Array of the variables
 * 
 * @return Value of the approximated integral
 */
double convergeintegrate_homogenstepcount(double start,double end,
		double (*fp)(double*),double precision,
		const int startisminfty,const int endisinfty,double* variables);



#endif //ifndef INTEGRATE_TRAPEZ_H