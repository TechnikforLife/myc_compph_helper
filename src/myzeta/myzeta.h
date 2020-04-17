/** 
 *  @file error_handler.h 
 *  @brief Provides functions,to handle errors
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 25.03.2020  	First Implementation of:
 *						zeta
 *						
 * 
 *  @todo change to using math.h
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1   
 */
 
#ifndef MYZETA_H
#define MYZETA_H

//set own precision value
#ifdef PRES
#undef PRES
#endif //ifdef PRES



/**
 * @define PRES
 * @brief Sets Precision to be used in testing rather the value is near 0
 */
#define PRES 1e-10



/**
 * @fn double zeta(double s);
 * @brief Function to calculate Zeta(s)
 *
 *
 * @param s Input value of the zeta function
 *
 * @return Output value of the zeta function
 */
double zeta(double s);
#endif //#ifndef MYZETA_H