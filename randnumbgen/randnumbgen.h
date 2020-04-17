/** 
 *  @file randnumbgen.h 
 *  @brief Provides functions to generate pseudorandom numbers
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 5.04.2020  	First Implementation of:
 *						randgenLehmerlongrange,Lehmer0_1trafo
 *						
 * 
 *  @todo at static to state
 * 
 *  @test compare to gsl
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1   
 */
 
#ifndef RANDNUMBGEN_H
#define RANDNUMBGEN_H



/**
 * @fn int* randgenLehmerlongrange(int* state);
 * @brief Generate a pseudorandom integer
 *
 * Generation of the pseudorandom number uses the Lehmer algorithm
 *
 * @param state Current state of the generator
 *
 * @return Pseusorandom integer
 */
int* randgenLehmerlongrange(int* state);



/**
 * @fn void Lehmer0_1trafo(int* integerstate,double* state);
 * @brief Generate a pseudorandom double in [0,1]
 *
 * "integerstate" generated by "randgenLehmerlongrange" gets converted 
 * into a double in the intervall [0,1]
 *
 * @param state Pointer to save the daouble in [0,1] into
 * @param integerstate Integerstate generated by "randgenLehmerlongrange"
 *
 */
void Lehmer0_1trafo(int* integerstate,double* state);
#endif //ifndef RANDNUMBGEN_H