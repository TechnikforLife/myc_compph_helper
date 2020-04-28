#include "derivatives.h"
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