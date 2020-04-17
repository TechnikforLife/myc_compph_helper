/** 
 *  @file error_handler.c
 *  @brief Provides functions,to handle errors
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 14.04.2020  First Implementation of: fatal_error, fatal_file_error 
 * 
 *  @todo prevent memory leak on error
 * 
 *  @test test different memory leak preventions
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1   
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "error_handler.h"
void fatal_error(const int condition,const char* message, const int errorcode,char const * fct){
	if(condition){
		if(message==NULL){
			message="";
		}
		//in defined cases the errorcode is decrypted into the corresponding error
		switch(errorcode){
			case FILE_OPEN_ERROR:
				fprintf(stderr,"FILE_OPEN_ERROR in %s: %s\n",fct,message);
				break;
			case FILE_READ_ERROR:
				fprintf(stderr,"FILE_READ_ERROR in %s: %s\n",fct,message);
				break;
			case FILE_GENERAL_STREAM_ERROR:
				fprintf(stderr,"FILE_GENERAL_STREAM_ERROR in %s: %s\n",fct,message);
				break;
			case MEMORY_ALLOCATION_ERROR:
				fprintf(stderr,"MEMORY_ALLOCATION_ERROR in %s: %s\n",fct,message);
				break;
			case MEMORY_REALLOCATION_ERROR:
				fprintf(stderr,"MEMORY_REALLOCATION_ERROR in %s: %s\n",fct,message);
				break;
			case STRING_COPY_ERROR:
				fprintf(stderr,"STRING_COPY_ERROR in %s: %s\n",fct,message);
				break;
			default:
				fprintf(stderr,"%s (in %s): Errorcode: %d\n",message,fct,errorcode);
		}
		exit(errorcode);
	}	
}
void fatal_file_error(FILE* stream,const char* message, const int errorcode){
	if(ferror(stream)){
		perror(message);
		fclose(stream);
		exit(errorcode);
	}	
}