/** 
 *  @file arrayhelpers.h 
 *  @brief Provides functions,to work with integer arrays
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 8.04.2020  	First Implementation of:
 *						output_integer_array, init_integer_array,
 *						rot_1_integer_array, rot_k_integer_array,
 *						reverse_integer_array, search_integer_array,
 *						readfileintarr, writefileintarr,						
 *						intarr_t
 *	@date 15.04.2020	First Implementation of:
 *						output_double_array,
 *						doublearr_t
 *						
 * 
 *  @todo change all functions to use intarr_t* (Pointer!)
 * 
 *  @test retest all functions with intarr_t*
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.2   
 */
 


#ifndef ARRAYHELPERS_H
#define ARRAYHELPERS_H



/**
 * @typedef typedef struct intarr_t
 * @brief Typedefinition of a struct to save integer arrays (pointer + length)
 */
typedef struct intarr_t{
	int* arrptr;
	int length;	
}intarr_t;



/**
 * @typedef typedef struct doublearr_t
 * @brief Typedefinition of a struct to save double arrays (pointer + length)
 */
typedef struct doublearr_t{
	double* dataptr;
	int length;	
}doublearr_t;



/**
 * @fn void output_double_array(doublearr_t arr);
 * @brief Prints the given double array on stdout
 *
 * Prints the array in a nice format on stdout
 *
 * @param arr Pointer to double array to print
 *
 */
void output_double_array(doublearr_t* arr);



/**
 * @fn void output_integer_array(const int * arr,const int n);
 * @brief Prints the given integer array on stdout
 *
 * Prints the array in a nice format on stdout
 *
 * @param arr Pointer to integer array to print
 * @param n length of the given integer array
 *
 */
void output_integer_array(const int * arr,const int n);



/**
 * @fn void init_integer_array(int* arr, const int n, const int initialval);
 * @brief Initializes the given array with "initialval"
 *
 * Initializes everyelement of "arr" with the value of "initialval"
 *
 * @param arr Pointer to integer array to initialize
 * @param n length of the given integer array
 * @param initialval Initialization value
 *
 */
void init_integer_array(int* arr, const int n, const int initialval);



/**
 * @fn void rot_1_integer_array(const int * arr,const int n);
 * @brief Rotates the given integer array by 1
 *
 *
 * @param arr Pointer to integer array to rotate
 * @param n length of the given integer array
 *
 */
void rot_1_integer_array(int * arr,const int n);



/**
 * @fn void rot_k_integer_array(const int * arr,const int n, int k);
 * @brief Rotates the given integer array by "k"
 *
 *
 * @param arr Pointer to integer array to rotate
 * @param n length of the given integer array
 * @param k Amount of digits to rotate by
 *
 */
void rot_k_integer_array(int * arr,const int n, int k);



/**
 * @fn void reverse_integer_array(const int * arr,const int n);
 * @brief Reverses the given integer array 
 *
 *
 * @param arr Pointer to integer array to reverse
 * @param n length of the given integer array
 *
 */
void reverse_integer_array(int * arr,const int n);



/**
 * @fn int search_integer_array(const int* arr1,const int n1,const int* arr2,const int n2);
 * @brief Searches for "arr1" in "arr2" and returns its starting location
 *
 * Searches for "arr1" in "arr2" and returns its starting location.
 * If "arr1 is not found in "arr2" -1 is being returned
 *
 * @param arr1 Pointer to integer array to search for
 * @param n1 length of the given integer array "arr1"
 * @param arr1 Pointer to integer array to search in
 * @param n1 length of the given integer array "arr2"
 *
 * @return Starting position of "arr1" in arr" or -1
 */
int search_integer_array(const int* arr1,const int n1,const int* arr2,const int n2);



/**
 * @fn intarr_t readfileintarr(const char* const filename);
 * @brief Reads the given file line by line and returns them as an integer array
 *
 * Reads the given file line by line and writes the value of each line 
 * in one spot of the returned array.
 *
 * @param filename String of the name of the file to read from
 *
 * @return Integer array of the read line
 */
intarr_t readfileintarr(const char* const filename);




/**
 * @fn void writefileintarr(intarr_t warr,const char* const filename);
 * @brief Writes the given integer array into the given file
 *
 * Writes the "warr" into the "filename",
 * each value occupies 1 line
 *
 * @param warr Integer to write to "filename"
 * @param filename String of the name of the file to write to
 *
 */
void writefileintarr(intarr_t warr,const char* const filename);

#endif //ifndef ARRAYHELPERS_H