#include <stdio.h>
#include "arrayhelpers.h"
#include <stdlib.h>

void output_double_array(doublearr_t* arr){
	printf("Array[%d]={",arr->length);
	for(int i=0;i<arr->length-1;++i){
		printf(" %f,",arr->dataptr[i]);
		if(!(i%5))printf("\n");
	}
	printf(" %f}\n",arr->dataptr[arr->length-1]);

}

void output_integer_array(/*array to print*/	const int * arr ,
						/*length of arr*/		const int n){
	printf("Array[%d]={",n);
	for(int i=0;i<n-1;++i){
		printf(" %d,",arr[i]);
	}
	printf(" %d}\n",arr[n-1]);

}

void init_integer_array(/*array to initialize*/		int * arr ,
						/*length of arr*/			const int n,
					/*value to initialize arr with*/const int initialval){

	for(int i=0;i<n;++i){
		arr[i]=initialval;
	}
}

void rot_1_integer_array(/*array to rotate*/	int * arr ,
						/*length of arr*/		const int n){
	int j=arr[n-1]; //saves last value, to put it at the beginning

	for(int i=n-1;i>0;--i){
		arr[i]=arr[i-1];

	}
	arr[0]=j;


}

void rot_k_integer_array(/*array to rotate*/	int * arr ,
						/*length of arr*/		const int n,
						/*amount of rotations*/	int k){

	//enable negative rotations
	if(k<0){
		k=n+k;
	}

	//temp array to copy the data of arr into
	int temp[n];
	for(int i=0;i<n;++i){
		temp[i]=arr[i];
	}

	//values from 0 till n-1-k are been writen
	for(int i=n-1;i>(k-1);--i){
		arr[i]=temp[i-k];
	}

	//values from n-k till n-1 are writen
	for(int i=0;i<k;++i){
		arr[i]=temp[n-k+i];
	}

}

void reverse_integer_array(/*array to print*/	int * arr ,
						/*length of arr*/		const int length){
	int temp;//temp
	int i, j;//index in first and secnd half to cycle through

	for (i=0,j=length-1;i<j;i++,j--){

		//swap values
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}

int search_integer_array(/*array to search in*/ const int* arr1,
						/*length of arr1*/		const int n1,
						/*array to search for*/	const int* arr2,
						/*length of arr2*/		const int n2){
	int test=0;
	for(int i=0;i<=(n1-n2);++i){
		/*only values with possibility to contain
		arr2 after them are being tested (n1-n2)*/
		if(arr1[i]==arr2[0]){
			//if the starting value fits the next values get tested
			test=1;
			for(int j=1;j<n2;++j){
				if(arr1[i+j]!=arr2[j]){
					test=0;
					break;
				}
			}
			//if all values fitted the findspot is returned
			if(test){
				return i;
			}
		}
	}
	return -1;
}



intarr_t readfileintarr(/*filename string to read*/ const char* const filename){
	intarr_t ret;
	FILE* file=NULL;//filestream pointer
	int x=0;//saves value of each line
	int len=-1;//len of the read array
	int n_read=1;//amount of read values each line
	int* arrmem=NULL;//pointer to the saved values

	//opening of "filename" to read
	file=fopen(filename,"r+");
	if(file==NULL){
		printf("Fileopen Error");
		exit(EXIT_FAILURE);
	}

	//reading of values until EOF or wrong format,
	//to determine the needed array size
	do{
		n_read=fscanf(file,"%d\n",&x);
		++len;
	}while(n_read==1);
	if(n_read!=EOF){
		printf("File read Error: File is not formated correctly!\n");
		exit(EXIT_FAILURE);
	}

	//memory allocation
	arrmem=(int*)malloc(sizeof(int)*len);
	if(arrmem==NULL){
		printf("RAM allocation Error");
		exit(EXIT_FAILURE);
	}

	//reading of values until EOF or Read error
	rewind(file);
	for(int i=0;i<len;++i){
		n_read=fscanf(file,"%d\n",&arrmem[i]);
		if(n_read!=1){
			printf("File read Error!\n");
			exit(EXIT_FAILURE);
		}
	}
	//cleanup
	ret.length=len;
	ret.arrptr=arrmem;
	fclose(file);
	return ret;
}
void writefileintarr(/*write array*/			intarr_t warr,
					/*filename string to read*/ const char* const filename){

	int n_write=0;//amount of written values each line
	FILE* file=NULL;//filestream pointer

	//opening of "filename" to write
	file=fopen(filename,"w");
	if(file==NULL){
		printf("Fileopen Error");
		exit(EXIT_FAILURE);
	}

	//writing of values from "warr"
	for(int i=0;i<warr.length;++i){
		n_write=fprintf(file,"%10d\n",warr.arrptr[i]);
		if(n_write<0){
			printf("File write Error!Element:%d,n:%d\n",i,n_write);
		}
	}

	//cleanup
	fclose(file);
}
