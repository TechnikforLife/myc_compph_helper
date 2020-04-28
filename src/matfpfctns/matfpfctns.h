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
 *  @date 28.04.2020	Moved derivate,root,integral functions 
 * 						to seperate moduls
 * 
 *  @todo cheack in valtable rather ferror gets set if the file does not exist
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.4
 */
 
#ifndef MATFPFCTNS_H
#define MATFPFCTNS_H

/**
 * @fn int valtable_double(double (*fp)(double),char* filename,double step, 
 * 						double start, double end);
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
int valtable_double(double (*fp)(double),char* filename,double step, 
					double start, double end);


#endif //ifndef MATFPFCTNS_H
