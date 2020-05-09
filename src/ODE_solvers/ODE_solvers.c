#include "../generalmemorymanager/generalmemorymanager.h"
#include "ODE_solvers.h"
#include <stdio.h>
#include <stdlib.h>

int bindex(int q,int r){
	return r+q*(q-1)/2;
}
void rk_mem_alloc(double**a,double**b,double**c,double**k,double**yh,int p,int noeq){
	*a=(double*)mem_alloc(sizeof (double)*p);
	*c=(double*)mem_alloc(sizeof (double)*p);
	*k=(double*)mem_alloc(sizeof (double)*p*noeq);
	*yh=(double*)mem_alloc(sizeof (double)*noeq);
	//printf ("%d\n",p);
	if(p>1){
		*b=(double*)mem_alloc(sizeof (double)*p*(p-1)/2);
	}
	
}

void rk_mem_free(double*a,double*b,double*c,double*k,double*yh,int p){
	mem_free(a);
	mem_free(c);
	mem_free(k);
	mem_free(yh);
	if(p>1){
		mem_free(b);
	}
	
}
void euler_cauchy(int noeq, double h, double t, double *y,
		   void (*dgl_rs) (int, double ,double *, double*),int call){
	static double *a,*b=NULL,*c,*k,*yh;
	static int p=1;
	if(call==1){
		rk_mem_alloc(&a,&b,&c,&k,&yh,p,noeq);
		a[0]=0;
		c[0]=1;
	}
	
	runge_kutta (noeq,h,t,y,dgl_rs,p,a,b,c,k,yh);
	if(call==-1){
		rk_mem_free(a,b,c,k,yh,p);
	}
}


void trapez(int noeq, double h, double t, double *y,
		   void (*dgl_rs) (int, double ,double *, double*),int call){
	static double *a,*b,*c,*k,*yh;
	static int p=2;
	if(call==1){
		rk_mem_alloc(&a,&b,&c,&k,&yh,p,noeq);
		a[0]=0;
		a[1]=1;
		//printf ("b=%d\n",bindex(0,0));
		b[bindex(1,0)]=1;
		c[0]=0.5;
		c[1]=0.5;
	}
	
	runge_kutta (noeq,h,t,y,dgl_rs,p,a,b,c,k,yh);
	if(call==-1){
		rk_mem_free(a,b,c,k,yh,p);
	}
}

void RK3(int noeq, double h, double t, double *y,
		   void (*dgl_rs) (int, double ,double *, double*),int call){
	static double *a,*b,*c,*k,*yh;
	static int p=3;
	if(call==1){
		rk_mem_alloc(&a,&b,&c,&k,&yh,p,noeq);
		a[0]=0.;
		a[1]=0.5;
		a[2]=1.;
		//printf ("b=%d\n",bindex(1,0));
		//printf ("b=%d\n",bindex(2,0));
		//printf ("b=%d\n",bindex(2,1));
		b[bindex(1,0)]=0.5;
		b[bindex(2,0)]=-1.;
		b[bindex(2,1)]=2.;
		//printf ("b=%e\n---------------------\n",b[bindex(1,0)]);
		//printf ("b=%e\n---------------------\n",b[bindex(2,0)]);
		//printf ("b=%e\n---------------------\n",b[bindex(2,1)]);
		c[0]=1./6.;
		c[1]=2./3.;
		c[2]=1./6.;
	}
	
	runge_kutta (noeq,h,t,y,dgl_rs,p,a,b,c,k,yh);
	if(call==-1){
		rk_mem_free(a,b,c,k,yh,p);
	}
}
void RK4(int noeq, double h, double t, double *y,
		   void (*dgl_rs) (int, double ,double *, double*),int call){
	static double *a,*b,*c,*k,*yh;
	static int p=4;
	if(call==1){
		rk_mem_alloc(&a,&b,&c,&k,&yh,p,noeq);
		a[0]=0.;
		a[1]=0.5;
		a[2]=0.5;
		a[3]=1.;
		//printf ("b=%d\n",bindex(1,0));
		//printf ("b=%d\n",bindex(2,0));
		//printf ("b=%d\n",bindex(2,1));
		b[bindex(1,0)]=0.5;
		b[bindex(2,0)]=0.;
		b[bindex(2,1)]=0.5;
		b[bindex(3,0)]=0.;
		b[bindex(3,1)]=0.;
		b[bindex(3,2)]=1.;
		//printf ("b=%e\n---------------------\n",b[bindex(1,0)]);
		//printf ("b=%e\n---------------------\n",b[bindex(2,0)]);
		//printf ("b=%e\n---------------------\n",b[bindex(2,1)]);
		c[0]=1./6.;
		c[1]=1./3.;
		c[2]=1./3.;
		c[3]=1./6.;
	}
	
	runge_kutta (noeq,h,t,y,dgl_rs,p,a,b,c,k,yh);
	if(call==-1){
		rk_mem_free(a,b,c,k,yh,p);
	}
}

void runge_kutta(int noeq,double h, double t,double *y,
				 void (*dgl_rs) (int, double ,double *, double*),
				 int p,double* a,double* b,double* c,double* k,double* yh){
	//k ist ein p mal noeq array
	double th=0.;
	double* kh=NULL;
	int i,j,q,r;
	for(q=0;q<p;q++){//durch alle p stufen hindurch gehen
					 // 
		for(i=0;i<noeq;i++){//yh best
			yh[i]=y[i];
			for(r=0;r<q;r++){
				//printf ("b(%d,%d)=%e\n",q,r,b[bindex(q,r)]);
				yh[i]+=b[bindex(q,r)]*k[i+r*noeq];
			}
		}
		
		//printf ("%e\n",a[q]);
		th=t+a[q]*h;
		kh=k+q*noeq;
		dgl_rs(noeq,th,yh,kh);//k best
		
		
		for(j=0;j<noeq;j++){//durch jede dimension durch gehen
			k[q*noeq+j]*=h;
		}
	}
	for(i=0;i<noeq;i++){
		for(q=0;q<p;q++){
			//if(i==0)
			//printf ("diff[%d]=%.20e\n",q,y[0]-y_check[0]);
			y[i]+=c[q]*k[q*noeq+i];
		}
	}
	
	
}