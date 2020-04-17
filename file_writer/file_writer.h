/** 
 *  @file file_writer.h
 *  @brief Provides functions,to write files in different formats
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *	@date 15.04.2020	First Implementation of:
 *						writedataset_l
 * 
 *  @todo implement function to write csv
 * 
 * 	@todo research: when ferror is set-> cleanup error handling
 *
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1
 */
 
#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include"../arrayhelpers/arrayhelpers.h"



/**
 * @fn void writedataset_l(doublearr_t* arr,const char* filename);
 * @brief Writes the dataset of the given array (length in the first row)
 *
 * 
 *	@param arr Double array to write
 * 	@param filename Filename of file to write into as string
 *
 */
void writedataset_l(doublearr_t* arr,const char* filename);



/**
 * 	@fn void writedatatable_l(doublearr_t* arr, double (*fp)(double), const char* filename)
 * 	@brief Writes the dataset of the given array (length in the first row)
 *
 * 	Prints f(dataset) into filename
 *
 *	@param arr Double array to write
 *	@param fp Function pointer to print f(dataset)
 * 	@param filename Filename of file to write into as string
 *
 */
void writedatatable_l(doublearr_t* arr, double (*fp)(double), const char* filename);

#endif // FILE_WRITER_H
