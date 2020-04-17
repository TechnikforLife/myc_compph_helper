/** 
 *  @file strswitchchar.h 
 *  @brief Provides functions,to execute char/string operations
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 14.04.2020  	First Implementation of:
 *						strswch
 *						
 * 
 *  @todo -
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1   
 */
 
#ifndef STRSWITCHCHAR_H
#define STRSWITCHCHAR_H

/**
 * @fn void strswch(char* str,int n, char chold, char chnew);
 * @brief replaces "chold" with "chnew" in "str"
 *
 * Replaces the char "chold" with "chnew" in the String "str" of length n
 *
 * @param str String to replace in
 * @param n Length of "str"
 * @param chold Old char
 * @param chnew New char
 *
 * @return Pointer to newly allocated string, read from filename
 */
void strswch(char* str,int n, char chold, char chnew);
#endif