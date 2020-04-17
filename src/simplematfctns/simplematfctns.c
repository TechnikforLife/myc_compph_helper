#include "simplematfctns.h"

double kumulativ_quadratic_sum(doublearr_t* arr){
	double sum;//value of the sum
	int i;//itterration variable

	//calculate the sum
	for(i=0;i<arr->length;i++){
		sum+=arr->dataptr[i];
	}

	//return the sum
	return sum;
}
