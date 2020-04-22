#include "../generalmemorymanager/generalmemorymanager.h"
#include "../error_handler/error_handler.h"
#include "../matfpfctns/matfpfctns.h"
#include "../simplematfctns/simplematfctns.h"
#include <math.h>
double f(double x){
	return pow(log(x),1/x);
}

double f_deriv(double x){
	return symfirstderivativeoptimized(x,f);
}
double f2(double x){
	return pow(x,-3);
}

double g(double x){
	return exp(-pow(fabs(x),0.1));
}
int main (int argc, char *argv[]){
	double x_0=3.;
	double h=1.;
	double firstexact=1./(x_0);
	double secexact=-1./(x_0*x_0);
	double thirdexact=2./(x_0*x_0*x_0);
	double firstderiv,secderiv,thirdderiv;
	double firsterror=1,secerror=1,thirderror=1;
	double firstlowest=2,seclowest=2,thirdlowest=2;
	int firstlowesti=0,seclowesti=0,thirdlowesti=0;
	for(int i=0;i<5200;i++){
		firstderiv=symfirstderivative(x_0,h,log);
		secderiv=symsecondderivative(x_0,h,log);
		thirdderiv=symthirdderivative(x_0,h,log);
		firsterror=fabs(firstderiv-firstexact);
		secerror=fabs(secderiv-secexact);
		thirderror=fabs(thirdderiv-thirdexact);
		if(firsterror<firstlowest){
			firstlowest=firsterror;
			firstlowesti=i;
		}
		if(secerror<seclowest){
			seclowest=secerror;
			seclowesti=i;
		}
		if(thirderror<thirdlowest){
			thirdlowest=thirderror;
			thirdlowesti=i;
		}
		h/=1.01;
		//printf("%e;%e\n",h,thirderror);
	}
	printf("1: %e\t2: %e\t3: %e\t(Errors)\n",firstlowest,
		   seclowest,thirdlowest);
	printf("1:%d\t2:%d\t3:%d\n",firstlowesti,seclowesti,thirdlowesti);
	
	/* h/=2;
	 * __float128:
	 * 1: 1.850372e-17	2: 6.167906e-18	3: 2.105312e-15	(Errors)
	 * 1:26	2:26	3:22
	 * 
	 * double:
	 * 1: 2.42533770844488572038e-12	2: 8.27842294714997706251e-10	3: 4.41515887183996369458e-08	(Errors)
	 * 1:16		2:12	3:10
	 * 
	 * float:
	 * 1: 2.54313151043517038374e-06	2: 3.39084201388950567946e-05	3: 1.44675925925930037863e-04	(Errors)
	 * 1:6	2:4	3:4
	 * 
	 */
	double x=1e-50;
	double xhighest=0.;
	for(int i=0;i<200;i++){
		if(1+x==1){
			xhighest=x;
		}
		x*=2;
	}
	/* double:
	 * 9.007199e-35 -50
	 * double:
	 * 1.038459e-16 -50
	 * float:
	 * 5.629500e-08 -22
	 */
	printf("Eps(double)=%e\n",xhighest);
	/**
	 * @note Part2:
	 */
	double root=rootmodifiedsecant (6, f_deriv, 1e-8);
	double realval=f_deriv(root);
	printf("Root: %e\tRealvalue: %.20e\n", root,realval);
	root=rootbisection (1,6, f_deriv, 1e-8);
	realval=f_deriv(root);
	printf("Root: %e\tRealvalue: %.20e\n", root,realval);
	/**
	 * @note Part3:
	 */
	//printf("%.15e\n----------\n", convergeintegrate (0, 3.14, sin, 1e-10,0, 0, integratetrapez));
	printf("Gamma(%e)=%e\n",-36.87,gammafunction (-36.87, 1e-4) );
	//printf("%e?=%e\n",0.5,convergeintegrate_homogenstepcount (1,10,f2, 1e-4,0,1) );
	//printf("%e?=%e\n",2.,convergeintegrate_homogenstepcount (1,10,g, 1e-4,1,1) );
	return EXIT_SUCCESS;
}
