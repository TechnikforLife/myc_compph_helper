#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "error_handler.h"

void fatal_error(const int condition,const char* message, const int errorcode,
				 char const * fct,char const * file,int line){
	/**
	 * @note 	The condition is tested and in defined  cases 
	 * 			a special error message is being displayed.
	 * 			At the end the memory is freed,
	 * 			if GENERALMEMORYMANAGER_H is being used.
	 * 
	 */
	if(condition){
		if(message==NULL){
			message="";
		}
		if(fct==NULL){
			fct="";
		}
		if(file==NULL){
			file="";
		}
		switch(errorcode){
			case FILE_OPEN_ERROR:
				fprintf(stderr,"FILE_OPEN_ERROR in %s (in file %s at %d): %s\n",
						fct,
						file,line,message);
				break;
			case FILE_READ_ERROR:
				fprintf(stderr,"FILE_READ_ERROR in %s (in file %s at %d): %s\n",
						fct,
						file,line,message);
				break;
			case FILE_GENERAL_STREAM_ERROR:
				fprintf(stderr,"FILE_GENERAL_STREAM_ERROR in file %s"
						" (in %s at %d): %s\n",fct,file,line,message);
				break;
			case STRING_COPY_ERROR:
				fprintf(stderr,"STRING_COPY_ERROR in %s (in file %s at %d):"
						" %s\n",fct,file,line,message);
				break;
			default:
				fprintf(stderr,"%s (in %s (in file %s at %d)): Errorcode: %d\n",
						message,fct,file,line,errorcode);
		}
		mem_free_all ();
		exit(errorcode);
	}
}

void fatal_file_error(FILE* stream,const char* message, const int errorcode){
	if(ferror(stream)){
		perror(message);
		fclose(stream);
		mem_free_all ();
		exit(errorcode);
	}
}
