#include <stdio.h>
#include <stdlib.h>
#include "matfpfctns.h"
#include <string.h>
#include <math.h>

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

double symfirstderivative(double x,double h,double (*fp)(double)){
	return (fp(x+h)-fp(x-h))/(2*h);
}

double symfirstderivativeoptimized(double x,double (*fp)(double)){
	double h=2e-5;
	return (fp(x+h)-fp(x-h))/(2*h);
}


double symsecondderivative(double x,double h,double (*fp)(double)){
	return (fp(x+h)+fp(x-h)-2*fp(x))/(h*h);
}

double symsecondderivativeoptimized(double x,double (*fp)(double)){
	double h=6e-4;
	return (fp(x+h)+fp(x-h)-2*fp(x))/(h*h);
}

double symthirdderivative(double x,double h,double (*fp)(double)){
	return ((fp(x+2*h)-fp(x-2*h))/2-fp(x+h)+fp(x-h))/(h*h*h);
}

double symthirdderivativeoptimized(double x,double (*fp)(double)){
	double h=2e-3;
	return ((fp(x+2*h)-fp(x-2*h))/2-fp(x+h)+fp(x-h))/(h*h*h);
}


double rootsecant(double a,double b,double (*fp)(double),double precision){
	/**
	 * Declarations:
	 * 
	 * @var x_i 	Current x
	 * @var x_im1	Prev x
	 * @var x_ip1	Next x
	 * @var i		Itteration variable
	 * 
	 */
	double x_i=a;
	double x_im1=b;
	double x_ip1=b+1;
	int i;
	
	/**
	 * @note	Try to estimate the root of "fp" with the given startvalues
	 * 			and to the given precision.
	 */
	for(i=0;i<10000;i++){
		x_ip1=x_i+(fp(x_i)*(x_im1-x_i))/(fp(x_i)-fp(x_im1));
		if(fabs(fp(x_ip1)-fp(x_i))<precision){
			break;
		}
		x_im1=x_i;
		x_i=x_ip1;
	}
	if(i==10000){
		printf("[WARNING] Could not reach given precision!\n");
	}
	return x_ip1;
}

double rootmodifiedsecant(double start,double (*fp)(double),double precision){
	/**
	 * Declarations:
	 * 
	 * @var x_i 	Current x
	 * @var x_ip1	Next x
	 * @var i		Itteration variable
	 * 
	 */
	double x_i=start;
	double x_ip1;
	int i;
	
	/**
	 * @note	Try to estimate the root of "fp" with the given startvalue
	 * 			and to the given precision.
	 */
	for(i=0;i<10000;i++){
		x_ip1=x_i-fp(x_i)/symfirstderivativeoptimized(x_i, fp);
		if(fabs(fp(x_ip1)-fp(x_i))<precision){
			break;
		}
		x_i=x_ip1;
	}
	if(i==10000){
		printf("[WARNING] Could not reach given precision!\n");
	}
	return x_ip1;
}



double rootbisection(double start,double end, double(*fp)(double),
					 double precision){
	/**
	 * Declarations:
	 * 
	 * @var upper 		Upper bound
	 * @var lower		Lower bound
	 * @var next		Next bound
	 * @var fpofupper	fp(upper)
	 * @var fpoflower	fp(lower)
	 * @var fpofnext	fp(next)
	 * @var i			Itteration variable
	 */
	double upper=end;
	double lower=start;
	double next;
	double fpofupper=fp(upper);
	double fpoflower=fp(lower);
	double fpofnext;
	int i;
	/**
	 * @note 	Check rather there could be only 1 root in the intervall
	 * 			and rather a boundary is already the root.
	 */
	if(fpofupper*fpoflower>0){
		printf("[ERROR] Could not find root in intervall:"
					" [%e,%e]!\n",start,end);
		exit(1);
	}
	if(fpofupper==0){
		return upper;
	}
	if(fpoflower==0){
		return lower;
	}
	
	/**
	 * @note In each step: 	Calculate the next possible boundary.
	 * 						Check in which subinterval the root is and 
	 * 						set it to be the new intervall.
	 * Stop if the Itteration limit or precision is reached.
	 */
	for(i=0;i<10000;i++){
		next=(lower+upper)/2;
		fpofnext=fp(next);
		if(fpofnext==0){
			return next;
		}
		if(fpofupper*fpofnext<0){
			lower=next;
			fpoflower=fp(lower);
		}else if(fpoflower*fpofnext<0){
			upper=next;
			fpofupper=fp(upper);
		}else{
			fprintf(stderr,"Sign error: No sign change found!\n");
			return next;
		}
		if(fabs(fpofupper-fpoflower)<precision){
			break;
		}
	}
	
	if(i==10000){
		printf("[WARNING] Could not reach given precision!\n");
	}
	return next;
}



double integrate(double* weights,double* x_sampling_points,int n,
				 double (*fp)(double)){
	/**
	 * Declarations:
	 * 
	 * @var integralapprox	Approximated value of the integral
	 */
	double integralapprox=0;
	for(int i=0;i<n;i++){
		integralapprox+=fp(x_sampling_points[i])*weights[i];
	}
	return integralapprox;
}



double integratetrapez(double start,double end,double (*fp)(double),unsigned int n){
	/**
	 * Declarations:
	 * 
	 * @var intervalllength 	length of the complet interval
	 * @var subintervalllength	length of the subinterval
	 * @var sum					value of the sum
	 * @var temp_f_x_i			initalized with f(x_0)
	 * @var f_x_i1				f(x_(i+1))
	 */
	double intervalllength=end-start;
	double subintervalllength=intervalllength/n;
	double sum=0.0;
	double temp_f_x_i=(*fp)(start);
	double f_x_i1=0.0;
	
	/**
	 * @note In each step: 	Calculate f(x_(i+1)) and 
	 * 						save f(x_(i+1)) for next itteration step
	 */
	for(int i=0;i<n;i++){
		f_x_i1=(*fp)(start+(i+1)*subintervalllength);
		sum+=temp_f_x_i+f_x_i1;
		temp_f_x_i=f_x_i1;
	}
	return sum*subintervalllength/2.;
}



double convergeintegrate(double start,double end,double (*fp)(double),
		double precision,
		double (*integrate_fp)(double,double,double(*fp)(double),unsigned int)){
	/**
	 * Declarations:
	 * @var old	Saves the previous value of the integral
	 * @var new	Saves the new value of the integral
	 */
	double old=integrate_fp(start,end,fp,1);	//old value
	double new=integrate_fp(start,end,fp,5);	//new value
	
	/**
	 * @note	Double the amount of Steps(=half the step size) 
	 * 			until the requested precision is reached.
	 */
	for(int n=10;fabs(new-old)>precision;n*=2){
		old=new;
		new=integrate_fp(start,end,fp,n);
	}
	return new;
}
