#include <math.h>
#include "numerov.h"
void init_ittertable(double start,double end,numerov_data_t* dat,
					double(*fg)(double),double(*fs)(double)){
	dat->h=(end-start)/(dat->n-1);
	for(int i=0; i<dat->n; i++){
		dat->r[i]=start+i*dat->h;
		dat->g[i]=fg(dat->r[i]);
		dat->s[i]=fs(dat->r[i]);
	}
}
void numerovup(numerov_data_t dat,int steps,double y0, double y1,double *y){
	double fakt_u_np1,fakt_u_n,fakt_u_nm1; /* Variablen fuer Numerov Faktoren */ 
	double fakt_s;    

	y[0]=y0;  /* belege erste Funktionswerte mit den Startwerten  */
	y[1]=y1;
   
	for(int i=1; i<steps+1; i++){
		fakt_u_np1=1.0+dat.h*dat.h*dat.g[i+1]/12.;
		fakt_u_n=1.0-5.*dat.h*dat.h*dat.g[i]/12.;
		fakt_u_nm1=1.0+dat.h*dat.h*dat.g[i-1]/12.;
		fakt_s=dat.h*dat.h/12.0*(dat.s[i+1]+10.0*dat.s[i]+dat.s[i-1]);
		y[i+1]=(fakt_s+2.0*fakt_u_n*y[i]-fakt_u_nm1*y[i-1])/fakt_u_np1; /* Vorwaertsiteration */ 
		
	}
}
void numerovdown(double *r,double *g,double *s,double h,int n,int steps,
				 double yn, double ynm1,double *y){
	double fakt_u_np1,fakt_u_n,fakt_u_nm1; /* Variablen fuer Numerov Faktoren */ 
	double fakt_s;    

	y[n-1]=yn;  /* belege erste Funktionswerte mit den Startwerten  */
	y[n-2]=ynm1;
   
	for(int i=n-2; i>n-steps-2; i--){
		fakt_u_np1=1.0+h*h*g[i+1]/12.;
		fakt_u_n=1.0-5.*h*h*g[i]/12.;
		fakt_u_nm1=1.0+h*h*g[i-1]/12.;
		fakt_s=h*h/12.0*(s[i+1]+10.0*s[i]+s[i-1]);
		y[i-1]=(fakt_s+2.0*fakt_u_n*y[i]-fakt_u_np1*y[i+1])/fakt_u_nm1;
	}
}