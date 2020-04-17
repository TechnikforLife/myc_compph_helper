/** 
 *  @file matfpfctns.h
 *  @brief Provides functions,to work with math function pointers
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 9.04.2020  valtable_double,integrate,integrate_cos,convergeintegrate
 * 
 *  @todo cheack in valtable rather ferror gets set if the file does not exist
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1   
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
 * @fn double integrate(double start, double end,double (*fp)(double), unsigned int n);
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
double integrate(double start, double end,double (*fp)(double), unsigned int n);



/**
 * @fn double integrate_cos(double x);
 * @brief integrates the cos from 0 to x
 *
 * It calls integrate convergeintegrate with precision 1e-5
 *
 * @param c End value of the integral
 * 
 * @return Value of the approximated integral
 */
double integrate_cos(double x);



/**
 * @fn double convergeintegrate(double start,double end,double (*fp)(double),double precision);
 * @brief approximates the integral of "fp" by trapezsum to the specifed "precision"
 *
 * Approximates the integral of "fp" by trapezsum
 * using integrate and the specifed "precision"
 * The given function ("fp") needs to have 1 dimensional In- and Output
 *
 * @param start Start value of the integral
 * @param end End value of the integral
 * @param fp Math function pointer to function to integrate
 * @param precision Difference between different subintervall trys
 * 
 * @return Value of the approximated integral
 */
double convergeintegrate(double start,double end,double (*fp)(double),double precision);
#endif //ifndef MATFPFCTNS_H