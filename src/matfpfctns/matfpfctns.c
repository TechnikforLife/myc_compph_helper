#include <stdio.h>
#include <stdlib.h>
#include "matfpfctns.h"
#include <string.h>

int valtable_double(double (*fp)(double),char* filename,double step, 
					double start, double end){
	/**
	 * Declarations:
	 * 
	 * @var file 	filestream pointer
	 * @var n_write	amount of values written in each line
	 * @var header	format of the header of the output file
	 * @var sep		seperation string if the file already exists
	 * 
	 */
	FILE * file=NULL;
	int n_write=0;
	char header[]="\tx\t\t\tf(x)\n";
	char sep[]="---------------\n";
	
	/**
	 * @note	Try to open the file: 
	 * 			If it exists, try to open it in append mode and write 
	 * 			seperation string at the end. Otherwise create a new file.
	 * 
	 */
	file=fopen(filename,"r");
	if(file!=NULL){
		file=fopen(filename,"a");
		if(file==NULL){
			fprintf(stderr,"Can not open file: %s\n",filename);
			return 1;
		}
		n_write=fprintf(file,"%s",sep);
		if(n_write!=strlen(sep)){
			fprintf(stderr,"Can not print \"%s\" to file: %s\n",sep,filename);
			return 1;
		}

	}else{
		file=fopen(filename,"w");
		if(file==NULL){
			fprintf(stderr,"Can not create file: %s\n",filename);
			return 1;
		}
	}

	/**
	 * @note	Write the header and dataset to the filestream 
	 * 			and check each time rather all characters were written.
	 * 
	 * 
	 */
	n_write=fprintf(file,"%s",header);
	if(n_write!=strlen(header)){
		fprintf(stderr,"Can not print \"%s\" to file: %s\n",header,filename);
		return 1;
	}
	for(double itter=start;itter<end;itter+=step){
		n_write=fprintf(file,"%10f\t%10f\n",itter,fp(itter));
		if(n_write!=22){
			fprintf(stderr,"Can not print \"%10f\t%10f\" to file: %s\n",itter,
					fp(itter),filename);
			return 1;
		}
	}
	
	fclose(file);
	return 0;
}
