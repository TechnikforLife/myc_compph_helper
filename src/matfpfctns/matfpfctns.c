#include <stdio.h>
#include <stdlib.h>
#include "matfpfctns.h"
#include <string.h>
#include <math.h>
int valtable_double(/*fct to itterrate*/	double (*fp)(double),
					/*file to write to*/	char* filename,
					/*step length*/			double step,
					/*start value*/			double start,
					/*end value*/			double end){
	FILE * file=NULL;//filestream pointer
	int n_write=0;//amount of values written in each line
	char header[]="\tx\t\t\tf(x)\n";//format of the header of the output file
	char sep[]="---------------\n";//seperation string if the file already exists

	//first try to open the file
	file=fopen(filename,"r");
	if(file!=NULL){//file already exist or other error

		//try to open the fill in append mode
		file=fopen(filename,"a");
		if(file==NULL){
			fprintf(stderr,"Can not open file: %s\n",filename);
			return 1;
		}

		//write seperation string at the end of the filestream
		n_write=fprintf(file,"%s",sep);
		if(n_write!=strlen(sep)){
			fprintf(stderr,"Can not print \"%s\" to file: %s\n",sep,filename);
			return 1;
		}

	}else{//create new file

		file=fopen(filename,"w");
		if(file==NULL){
			fprintf(stderr,"Can not create file: %s\n",filename);
			return 1;
		}
	}

	//write the header to the filestream
	n_write=fprintf(file,"%s",header);
	if(n_write!=strlen(header)){
		fprintf(stderr,"Can not print \"%s\" to file: %s\n",header,filename);
		return 1;
	}

	//write a data set in every line
	for(double itter=start;itter<end;itter+=step){
		n_write=fprintf(file,"%10f\t%10f\n",itter,fp(itter));

		//check rather the amount of written characters is correct
		if(n_write!=22){
			fprintf(stderr,"Can not print \"%10f\t%10f\" to file: %s\n",itter,fp(itter),filename);
			return 1;
		}
	}

	//cleanup
	fclose(file);
	return 0;
}


double integrate(/*start of interval*/	double start,
				/*end of interval*/		double end,
				/*fct to integrate*/	double (*fp)(double),
				/*#subintervall to divide
				[start,end] into*/		unsigned int n){

	double intervalllength=end-start;//length of the complet interval
	double subintervalllength=intervalllength/n;//length of the subinterval
	double sum=0.0;//value of the sum
	double temp_f_x_i=(*fp)(start);//initalized with f(x_0)
	double f_x_i1=0.0;//f(x_(i+1))

	for(int i=0;i<n;i++){

		//calculate f(x_(i+1))
		f_x_i1=(*fp)(start+(i+1)*subintervalllength);
		sum+=temp_f_x_i+f_x_i1;

		//save f(x_(i+1)) for next itteration step
		temp_f_x_i=f_x_i1;
	}

	//return value of estimated integral
	return sum*subintervalllength/2.;
}

double integrate_cos(double x){
	return convergeintegrate(0,x,cos,1e-5);

}

double convergeintegrate(/*start of interval*/	double start,
				/*end of interval*/		   		double end,
				/*fct to integrate*/			double (*fp)(double),
				/*precision at which to stop*/	double precision){
	double old=integrate(start,end,fp,1);	//old value
	double new=integrate(start,end,fp,5);	//new value

	for(int n=10;fabs(new-old)>precision;n+=10){
		//new->old
		old=new;

		//get new value
		new=integrate(start,end,fp,n);
	}
	return new;
}






