/** 
 *  @file arraysorters.h 
 *  @brief Provides functions,to sort arrays
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 14.04.2020  	First Implementation of:
 *						naiv_sort, bucket_sort, merge 
 *						mergesort, lexiocompare
 *						
 * 
 *  @todo implement for other data types(double, etc)
 *
 * 	@todo change all functions to use intarr_t* (Pointer!)
 * 
 *  @test test qsort with other compare functions
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1   
 */

#ifndef ARRAYSORTERS_H
#define ARRAYSORTERS_H



/**
 * @define MAX
 * @brief Sets maximum of the used buckets in bucket_sort
 */
#define MAX 2000



/**
 * @define MAX
 * @brief Sets minimum of the used buckets in bucket_sort
 */
#define MIN -20



/**
 * @fn void naiv_sort(int * arr,const int n);
 * @brief Function to sort an integer array "arr"
 *
 * Every element is looped through and for each element 
 * it is determined wether it has the lowest value of 
 * the remaining array Complexity:n^2
 *
 * @param arr Pointer to integer array to sort
 * @param n length of the given integer array
 *
 */
void naiv_sort(int *,const int);



/**
 * @fn void bucket_sort(int * arr,const int n);
 * @brief Function to sort an integer array "arr"
 *
 * The array is being sorted using the bucket sort algorithm
 *
 * @param arr Pointer to integer array to sort
 * @param n length of the given integer array
 *
 */
void bucket_sort(int * arr,const int n);



/**
 * @fn int* merge(int* list1, int n, int* list2, int m);
 * @brief Function to merge 2 given arrays
 *
 * The given sorted arrays get merged into a sorted array
 *
 * @param list1 Pointer to the first integer array to merge
 * @param n length of the first integer array
 * @param list2 Pointer to the second integer array to merge
 * @param n length of the second integer array
 *
 * @return Pointer to the merged (sorted) array
 */
int* merge(int* list1, int n, int* list2, int m);



/**
 * @fn void mergesort(int* arr, int n);
 * @brief Function to sort an integer array "arr"
 *
 * The array is being sorted using the merge sort algorithm
 *
 * @param arr Pointer to integer array to sort
 * @param n length of the given integer array
 *
 */
void mergesort(int* arr, int n);



/**
 * @fn int lexiocompare(const void* left, const void* right);
 * @brief Function to compare 2 entries used with qsort from stdlib
 *
 * The given entry get compared using strcmp
 *
 * @param left Pointer to the left element (string)
 * @param right Pointer to the right element (string)
 *
 * @return The values represent: left*right, with * being: =(0),<(<0),>(>0)
 */
int lexiocompare(const void* left, const void* right);
#endif //ifndef ARRAYSORTERS_H