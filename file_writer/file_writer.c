/** 
 *  @file file_writer.c
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
 * 	@todo implement new test for writting numbers
 * 
 * 	@todo research: when ferror is set-> cleanup error handling
 *
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1
 */
 
#include "file_writer.h"
#include "../error_handler/error_handler.h"


#include <stdlib.h>
#include <string.h>

void writedataset_l(doublearr_t* arr,const char* filename){
	FILE* outptfilestream=NULL;//Output Filestream, opened from "filename"
	const char* fct=__func__;//Functionname, used in error case
	int n_write=0;//amount of characters written
	int i=0;//Itterattion variable
	
	//"filename" is being opened as filestream in "outptfilestream"
	outptfilestream=fopen(filename,"w");
	fatal_file_error(outptfilestream,fct,FILE_GENERAL_STREAM_ERROR);
	
	//write the length of the dataset
	n_write=fprintf(outptfilestream,"%d\n",arr->length);
	//fatal_error(n_write!=1,NULL,FILE_READ_ERROR,fct);
		
	//write the values of the array
	for(i=0;i<arr->length;++i){
		n_write=fprintf(outptfilestream,"%f\n",arr->dataptr[i]);
		//fatal_error(n_write!=1,NULL,FILE_READ_ERROR,fct);
		printf("Written %d chars.\n",n_write);
	}
	
	//cleanup
	fclose(outptfilestream);
	
}

void writedatatable_l(doublearr_t* arr, double (*fp)(double), const char* filename){
	FILE* outptfilestream=NULL;//Output Filestream, opened from "filename"
	const char* fct=__func__;//Functionname, used in error case
	int n_write=0;//amount of characters written
	int i=0;//Itterattion variable
	
	//"filename" is being opened as filestream in "outptfilestream"
	outptfilestream=fopen(filename,"w");
	fatal_file_error(outptfilestream,fct,FILE_GENERAL_STREAM_ERROR);
	
	//write the length of the dataset
	n_write=fprintf(outptfilestream,"%d\n",arr->length);
	//fatal_error(n_write!=1,NULL,FILE_READ_ERROR,fct);
	
	//write header
	n_write=fprintf(outptfilestream,"x\t\tf(x)\n");
	//write the values of the array
	for(i=0;i<arr->length;++i){
		n_write=fprintf(outptfilestream,"%6.4f\t%6.4f\n",arr->dataptr[i],fp(arr->dataptr[i]));
		//fatal_error(n_write!=1,NULL,FILE_READ_ERROR,fct);
		//printf("Written %d chars.\n",n_write);
	}
	
	//cleanup
	fclose(outptfilestream);
	
}