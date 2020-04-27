/** 
 *  @file specialfctns.h 
 *  @brief Provides  approximations to special fctns
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 27.04.2020 	First Implementation of: xlogofx_y_inv
 * 
 *  @todo 
 * 
 *  @test 
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1
 */
#ifndef SPECIALFCTNS_H
#define SPECIALFCTNS_H
/**
 * @fn double xlogofx_y_inv(double y);
 * @brief Calculates x(y)
 *
 * Calculates x(y) which is the inversion of x*log(x)=y
 *
 * @param y Value of which x(y) should be calculated
 *
 * @return Approximation of x(y)
 */
double xlogofx_y_inv(double y);
#endif // SPECIALFCTNS_H
