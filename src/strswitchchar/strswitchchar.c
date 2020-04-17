#include "strswitchchar.h"
#include <stdio.h>

void strswch(char str[],int n, char chold, char chnew){
	//iterrate through str and swap chold for chnew
	for(int i=0;i<n;i++){
		if(str[i]==chold){
			str[i]=chnew;
		}

	}
}
