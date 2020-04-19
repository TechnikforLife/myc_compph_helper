#include "file_reader.h"
#include "../error_handler/error_handler.h"
#include "../generalmemorymanager/generalmemorymanager.h"


#include <stdlib.h>
#include <string.h>



char* readbyline(const char*filename){
	//Declaration:
	char buf[R_BUFFERSIZE];//Linebuffer
	char* temp=NULL;//Temporary Pointer, used to check memory allocation error
	char* str=NULL;//Output String
	char* emptyline="\n";//String to replace empty Lines
	FILE* inptfilestream=NULL;//Input Filestream, opened from "filename"
	int buflen=0;//saves the string length of the linebuffer
	int startsempty=0;//saves rather file started with emptylines
	size_t len=0;//saves the total length of str (with \0)

	//"filename" is being opened as filestream in "inptfilestream"
	inptfilestream=fopen(filename,"r");
	fatal_error(inptfilestream==NULL,NULL,FILE_OPEN_ERROR,__func__,__FILE__,
				__LINE__);

	//read first line or until the buffer is full
	fatal_error(fgets(buf,sizeof(buf),inptfilestream)==NULL,
		NULL,FILE_READ_ERROR,__func__,__FILE__,__LINE__);
	fatal_file_error(inptfilestream,__func__,FILE_GENERAL_STREAM_ERROR);

	//replacement of "\r\n ->\n"
	buflen=strlen(buf);
	if(buflen>1&&buf[buflen-2]=='\r'){
		buf[buflen-2]='\n';
		buf[buflen-1]='\0';
	}

	//Memory allocation
	len=(strlen(buf)+1)*sizeof(char);//with \0
	str=mem_alloc (len);

	//copieng of buffer to final string
	fatal_error(strncpy(str,buf,len-1)==NULL,
		NULL,STRING_COPY_ERROR,__func__,__FILE__,__LINE__);

	//test wether the line is empty
	if(str[0]=='\n'){
		startsempty=1;
		len=1;
		//"len"=1 because of \0,
		//so that len has the right size for later reallocations of memory
	}

	//read lines until the end of "filename" is reached
	while(!feof(inptfilestream)){

		//read next line or until the buffer is full
		if(fgets(buf,sizeof(buf),inptfilestream)==NULL){
			fprintf(stdout,"[WARNING] Read empty line from %s in %s\n",filename,
					__func__);

			//in case of a completly empty line buf=emptyline
			fatal_error(strncpy(buf,emptyline,R_BUFFERSIZE-1)==NULL,
				NULL,STRING_COPY_ERROR,__func__,__FILE__,__LINE__);
		}

		//replacement of "\r\n ->\n"
		buflen=strlen(buf);
		if(buflen>1&&buf[buflen-2]=='\r'){
			buf[buflen-2]='\n';
			buf[buflen-1]='\0';
		}

		//empty lines don not get copied into the final string
		if(buf[0]=='\n'){
			continue;
		}

		//reallocation of needed memory
		len+=(strlen(buf))*sizeof(char);
		temp=mem_realloc(str,len);
		str=temp;

		//if "filename" started with empty lines,
		//then the first not empty line needs to go at the beginning of "str"
		if(startsempty){
			fatal_error(strncpy(str,buf,len-1)==NULL,
				NULL,STRING_COPY_ERROR,__func__,__FILE__,__LINE__);
			startsempty=0;

		//otherwise "str" is appened by "buf"
		}else{
			fatal_error(strncat(str,buf,strlen(buf))==NULL,
				NULL,STRING_CAT_ERROR,__func__,__FILE__,__LINE__);
		}
	}

	//cleanup
	fclose(inptfilestream);

	//add trailing \n if it does not exist already
	if(str[len-2]!='\n'){
		len++;
		temp=mem_realloc(str,len);
		str=temp;
		str[len-2]='\n';
		str[len-1]='\0';
	}
	return str;
}


doublearr_t* readdataset_l(const char* filename){
	FILE* inptfilestream=NULL;//Input Filestream, opened from "filename"
	const char* fct=__func__;//Functionname, used in error case
	int len=0;//length of dataset
	int n_read=0;//amount of values read
	double* dataset=NULL;//pointer to the read dataset
	int i=0;//Itterattion variable
	doublearr_t* darr=NULL;//pointer to the returned doublearr_t

	//memory allocation for the returned doublearr_t
	darr=mem_alloc(sizeof(doublearr_t));

	//"filename" is being opened as filestream in "inptfilestream"
	inptfilestream=fopen(filename,"r");
	fatal_file_error(inptfilestream,fct,FILE_GENERAL_STREAM_ERROR);

	//read the length of the dataset
	n_read=fscanf(inptfilestream,"%d\n",&len);
	fatal_error(n_read!=1,NULL,FILE_READ_ERROR,__func__,__FILE__,__LINE__);

	//memory allocation for dataset
	dataset=mem_alloc(len*sizeof(double));

	//read the values of the dataset until EOF
	for(i=0;i<len;++i){
		n_read=fscanf(inptfilestream,"%lf\n",&dataset[i]);
		fatal_error(n_read!=1,NULL,FILE_READ_ERROR,__func__,__FILE__,__LINE__);
	}

	//cleanup
	fclose(inptfilestream);

	//save data
	darr->length=len;
	darr->dataptr=dataset;
	return darr;
}

doublearr_t* readdatasetbin_l(const char* filename){
	FILE* inptfilestream=NULL;//Input Filestream, opened from "filename"
	const char* fct=__func__;//Functionname, used in error case
	int len=0;//length of dataset
	size_t b_read=0;//amount of bytes read
	double* dataset=NULL;//pointer to the read dataset
	doublearr_t* darr=NULL;//pointer to the returned doublearr_t

	//memory allocation for the returned doublearr_t
	darr=mem_alloc(sizeof(doublearr_t));

	//"filename" is being opened as filestream in "inptfilestream"
	inptfilestream=fopen(filename,"r");
	fatal_file_error(inptfilestream,fct,FILE_GENERAL_STREAM_ERROR);

	//read the length of the dataset
	b_read=fread(&len,sizeof(int),1,inptfilestream);
	printf("%ld\n",b_read);
	fatal_error(b_read!=1,"length read",FILE_READ_ERROR,__func__,__FILE__,
				__LINE__);

	//memory allocation for dataset
	dataset=mem_alloc(len*sizeof(double));

	//read the values of the dataset until EOF
	b_read=fread(dataset,sizeof(double),len,inptfilestream);
	printf("%ld\n",b_read);
	fatal_error(b_read!=len,"data read",FILE_READ_ERROR,__func__,__FILE__,
				__LINE__);


	//cleanup
	fclose(inptfilestream);

	//save data
	darr->length=len;
	darr->dataptr=dataset;
	return darr;

}
