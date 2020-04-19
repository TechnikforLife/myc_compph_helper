/** 
 *  @file file_reader.h 
 *  @brief Provides functions,to read files in different formats
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 11.04.2020 	First Implementation of: readbyline
 *	@date 15.04.2020	First Implementation of:
 *						readdataset_l
 * 
 *  @todo implement function to read csv, merge normal and binary reader
 * 
 *  @test readbyline test with different newline formats
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.2 
 */
#ifndef FILE_READER_H
#define FILE_READER_H

#include"../arrayhelpers/arrayhelpers.h"

/**
 * @define define R_BUFFERSIZE
 * @brief defines read buffer size
 */
#define R_BUFFERSIZE 256



/**
 * @fn char* readbyline(const char* filename)
 * @brief Function to read file "filename" char by char
 *
 * The file is been read line by line(or till the buffer is full).
 * Empty lines are beeing skipted (\n in buffer).
 * Windows style newline (\r\n) is beeing replaced 
 * by Unix style newline (\n).
 * The returned String ends with \n.
 *
 * @param filename Filename of file to read from as string
 *
 * @return Pointer to newly allocated string, read from filename
 */
char* readbyline(const char* filename);



/**
 * @fn char* readdataset_l(const char* filename);
 * @brief Reads the dataset of the given file(length in the first row)
 *
 * 
 *
 * @param filename Filename of file to read from as string
 *
 * @return Pointer to newly allocated double array
 */
doublearr_t* readdataset_l(const char* filename);




/**
 * @fn char* readdatasetbin_l(const char* filename);
 * @brief Reads the dataset of the given binary file(length in the first row)
 *
 * @param filename Filename of file to read from as string
 *
 * @return Pointer to newly allocated double array
 */
doublearr_t* readdatasetbin_l(const char* filename);

#endif // FILE_READER_H
