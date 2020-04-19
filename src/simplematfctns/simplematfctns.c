#include "simplematfctns.h"
#include <stdlib.h>
doublearr_t* kumulativ_quadratic_sum(doublearr_t* arr){
	doublearr_t* sum;//array of the sums
	int i;//itterration variable
	sum=malloc(sizeof (doublearr_t));
	if(sum==NULL)exit(1);
	sum->dataptr=malloc (sizeof(double)*arr->length);
	if(sum->dataptr==NULL)exit(1);
	//calculate the sum for the first element
	sum->dataptr[0]=arr->dataptr[0]*arr->dataptr[0];
	for(i=1;i<arr->length;i++){
		sum->dataptr[i]=sum->dataptr[i-1]+arr->dataptr[i]*arr->dataptr[i];
	}

	//return the sum
	return sum;
}
