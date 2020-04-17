#include <stdio.h>
#include <stdlib.h>
#include "../arrayhelpers/arrayhelpers.h"
#include <string.h>
#include "arraysorters.h"

void naiv_sort(/*array to sort*/	int * arr ,
			/*length of arr*/		const int n){
	int minindex=0;//saves the index with the smallest value for the remaining array
	int temp=0;//saves the value of the currently processed value

	for(int i=0;i<n;++i){
		temp=arr[i];
		minindex=i;

		//check rather any of the remaining values are smaller than arr[minindex]
		for(int j=(i+1);j<n;++j){//i+1 because minindex=i
			if(arr[j]<=arr[minindex]){
				minindex=j;
			}
		}

		//swap the smallest value of the remaining array to position i
		arr[i]=arr[minindex];
		arr[minindex]=temp;
	}
}

void bucket_sort(/*array to sort*/	int * arr ,
			/*length of arr*/		const int n){
	int buckets[MAX-(MIN)+1]={0};//array to count the amount of values in each bucket
	int k=0;

	for(int i=0;i<n;++i){

		//Test rather all values are in [MIN,MAX]
		if(arr[i]<MIN){
			printf("Wrong MIN!\n");
			exit(EXIT_FAILURE);
		}
		if(arr[i]>MAX){
			printf("Wrong MAX!\n");
			exit(EXIT_FAILURE);
		}

		//count the amount of elements in each buckets
		buckets[arr[i]-MIN]++;
	}

	//write the values determent by "buckets" into "arr"
	for(int i=0;i<(MAX-MIN+1);++i){
		for(int j=0;j<buckets[i];j++){
			arr[k]=i+MIN;
			k++;
		}
	}
}

int* merge(/*1.array*/				int* list1,
			/*length of 1.array*/	int n,
			/*2.array*/				int* list2,
			/*length of 2.array*/	int m){
	int* ret=NULL;//Pointer to the merged array
	int j=0;//counter for the first array
	int i=0;//counter for the second array

	//memory allocation for the merged array
	ret=(int*)malloc(sizeof(int)*(n+m));
	if(ret==NULL){
		fprintf(stderr,"RAM allocation Error");
		exit(EXIT_FAILURE);
	}

	//merge until the end of one array is reached
	while(i<n&&j<m){

		//merge in a sorted way
		if(list1[i]<list2[j]){
			ret[i+j]=list1[i];
			++i;
		}else{
			ret[i+j]=list2[j];
			++j;
		}
	}

	//append the rest of the not finished array
	if(i<n){
		for(;i<n;++i){
			ret[i+j]=list1[i];
		}
	}else{
		for(;j<m;++j){
			ret[i+j]=list2[j];
		}
	}
	return ret;
}

void mergesort(/*list to mergesort*/	int* list,
				/*length of said list*/	int n){

	int m=0;//saves the point to split "list"
	int* arr1=NULL;//pointer to the first half of "list"
	int* arr2=NULL;//pointer to the second half of "list"
	int* temp=NULL;//pointer to the merged array

	//test rather the length is valid
	if(n<0){
		fprintf(stderr,"Invalid length\n");
		exit(EXIT_FAILURE);
	}
	if(n>1){

		if(n%2){//uneven
			m=(n-1)/2;
		}else{//even
			m=n/2;
		}

		//set the pointers to split "list" (this way it is memory efficient)
		arr1=list;
		arr2=list+m;

		//split each half even further
		mergesort(arr1,m);
		mergesort(arr2,n-m);

		//merge them together again
		temp=merge(arr1,m,arr2,n-m);

		//copy the returned sorted merged array to the input array
		for(int i=0;i<n;i++){
			list[i]=temp[i];
		}

		//cleanup
		free(temp);
	}
}

int lexiocompare(const void* left, const void* right){
	//pointer to elements get passed by qsort
	//=char*const*
	char*const*leftcharptr=left;
	char*const*rightcharptr=right;
	//char*const* needs to be dereferenced to get the str ptr
	char*const leftstr=*leftcharptr;
	char*const rightstr=*rightcharptr;
	//use strcmp to compare
	return strcmp(leftstr,rightstr);
}
