/** 
 *  @file mysolver.h 
 *  @brief Provides functions to solve equations
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 30.03.2020  	First Implementation of:
 *						squaresolv
 * 
 *  @todo Implement other functions (complex)
 * 
 *  @todo Implement own type for return objects
 *
 *  @test test complex functionality
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1   
 */
 
#ifndef MYSOLVER_H
#define MYSOLVER_H

//set own precision value
#ifdef PRES
#undef PRES
#endif //ifdef PRES



/**
 * @define PRES
 * @brief Sets Precision to be used in testing rather the value is near 0
 */
#define PRES 1e-30


/**
 * @fn void fatal_error(const int condition,const char* message, const int errorcode,const char * fct);
 * @brief Function to solve a quadtratic equation
 *
 * This function calculates the real solutions for the equation:
 * abc[0]*x^2+abc[1]*x+abc[2]=0
 *
 * @param abc Pointer to double array countaining the values of parameters a,b and c
 * @param sol Pointer to the array to save the solutions into
 *
 * @return Amount of solutions found (-1 if infinitly many)
 */
int squaresolv(double* abc,double* sol);
#endif //ifndef MYSOLVER_H