#include "../generalmemorymanager/generalmemorymanager.h"
#include "../ODE_solvers/ODE_solvers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double kappa=0.5;
void RuKu_3 ( int nDifEqu, /* # der Differentialgleichungen */
              double h, /* Schrittweite */
              double t, /* Kurvenparameter */
              double y[], /* Bahnkurve [nDifEqu] */  
              double yh[], double k1[], double k2[], double k3[], /* Hilfsfelder [nDifEqu] */
              void (*derhs) ( int, double, double[], double[] ) /* Funktion zur Berechnung der rechten Seite */
    ){

/* Berechnet 1 Runge-Kutta Schritt (3. Ordnung) zur Loesung des DG-Systems:
   y'(t) = f(y(t),t); y \in R^n */

/* Variablen */
  double h2;
  int i;

  h2 = 0.5 * h;
  (*derhs)( nDifEqu, t   , y , k1 );
  for (i=0; i<nDifEqu; i++) { yh[i] = y[i] + h2 * k1[i]; }
  (*derhs)( nDifEqu, t+h2, yh, k2 );
  for (i=0; i<nDifEqu; i++) { yh[i] = y[i] - h  * k1[i] + 2 * h * k2[i]; }
  (*derhs)( nDifEqu, t+h2, yh, k3 );
  for (i=0; i<nDifEqu; i++) { y[i] += 
          ( h2 * (k1[i]+k3[i]) + 2 * h * k2[i] ) / 3; }

}
void generel_osz(int noeq,double t, double* y,double* f){
	if(noeq!=2){
		fprintf (stderr,"The amount of equations is not fitting!");
		exit (EXIT_FAILURE);
	}
	f[0]=y[1];
	f[1]=y[0]-kappa*y[0]*y[0]*y[0];
}
void harm_osz(int noeq,double t,double* y,double* f){
	if(noeq!=2){
		fprintf (stderr,"The amount of equations is not fitting!");
		exit (EXIT_FAILURE);
	}
	f[0]=y[1];
	f[1]=-y[0];
}

int main(){
	mem_init (0);
	double h,t0,y_0,tend=10,tstep,v_0;  /* Schrittweite, startpunkt, Startwert
                                 Endpunkt, Schritt fuer Ausgabe */ 
	int noeq=2;                  /* feste Vorgabe der Anzahl der Gleichungen */ 
	//double exact;
	//double diff=10;    /* Variablen, um Ergebnis zu speichern und vergleichen*/  
	double *y;         /* Zeiger auf Speicherplaetze, die double enthalten */

	double t,tprint; 
	//double*f,*k1,*k2,*k3;
	/* Eingabe der Parameter */ 
	printf("Bitte geben Sie h,t0,y_0,v_0,tend und tstep ein: \n");
	int err=scanf(" %le %le %le %le %le %le",&h,&t0,&y_0,&v_0,&tend,&tstep);  
	if(err!=6)printf ("ALARM\n");
	/* malloc reserviert Speicher fuer Feld mit y Werten und Hilfsfeld */ 
	y=mem_alloc(sizeof(double)*noeq);
	
	y_check=mem_alloc(sizeof(double)*noeq);     
	//f=mem_alloc(sizeof(double)*noeq); 
	//k1=mem_alloc(sizeof(double)*noeq);   
	//k2=mem_alloc(sizeof(double)*noeq);   
	//k3=mem_alloc(sizeof(double)*noeq);   
	    

	printf("\n   %20s %20s %20s \n","t","RK3","diff");
	int counter=100;
	
	
	int first=1;
	//double diffold=0;
	//printf("%e,%e,%e\n",fabs(t0),fabs(tend),h);
	FILE* stream2=fopen("data/ueb5_2_d.dat","w");
	int per=0;
	double period=0;
	int issecond_extr=0;
	double deriv=0;
	int isfirst=1;
	int hasfallen=0;
	double* periods;
	periods=(double*)mem_alloc (sizeof (double)*counter);
	for(;y_0<100;y_0+=0.1){
	
	first=1;
	y[0]=y_0;
	y[1]=v_0;
	y_check[0]=y_0;
	y_check[1]=v_0;
	tprint=t0;
	per=0;
	period=0;
	issecond_extr=0;
	deriv=0;
	isfirst=1;
	hasfallen=0;
	for(t=t0;fabs(t)<=fabs(tend);){
		if(fabs(t)>=tprint) /* Naechsten Ausgabepunkt erreicht?*/ {
			//exact=y_0*cos(t)+v_0*sin(t);           /* known exact value */ 
			//diff=fabs((y_check[0]-y[0]));
			   /* and rel. error */
			//printf("   %20.5le",t);
			//printf("   %20.5le",y_check[0]);
			//printf("   %20.5le",y[0]);
			//printf("   %20.5le\n",diff);
			//fprintf(stream2,"   %20.5le;",t);
			//fprintf(stream2,"   %20.5le;",y_check[0]);
			//fprintf(stream2,"   %20.5le;",y[0]);
			//fprintf(stream2,"   %20.5le\n",diff);
			//printf("   %20.5le",fabs((exact-y_check[0])));
			//printf("   %20.5le\n",fabs(diff-diffold));
			//diffold=diff;
			//printf("   %20.5le %20.5le %20.5le %20.5le %20.5le %20.5le\n",
			//	   t,exact,y[0],diff,y_check[0],fabs((exact-y_check[0])/exact));
			tprint+=tstep;  /* Ausgabe und naechsten Punkt bestimmen */
		}
 		     
		/* Dgl.schritt ausfuehren */ 
		      
		RK4 (noeq,h,t,y,generel_osz,first );
		//RuKu_3(noeq,h,t,y_check,f,k1,k2,k3,generel_osz);
		first=0;
		t+=h;
		if(per<counter){
			if(fabs(y[1])<y_0/10){
				if(isfirst){
					deriv=fabs(y[1]);
					isfirst=0;
					hasfallen=0;
				}else{
					if(fabs(y[1])<deriv){
						deriv=fabs(y[1]);
						hasfallen=1;
					}else{
						if(hasfallen){
							if(issecond_extr){
								periods[per]=t-h;
								per++;
								issecond_extr=0;
							}else{
								issecond_extr=1;
							}
							
							isfirst=1;
						}else{
							isfirst=1;
						}
					}
				}
			}
			
		}
	}  
	RK4 (noeq,h,t,y,generel_osz,-1 ); 
	
	if(per>0){
		printf("%e,%d\n",y_0,per);
		period=periods[0]-t0;
		for(int j=1;j<per;j++){
			period+=periods[j]-periods[j-1];
		}
		period/=per;
		fprintf(stream2,"%20.5le;%20.5le\n",y_0,period);
		
		
	}
	}
			  fclose(stream2);
	/*
	t0=0;
	tend=20;
	tstep=0.2;
	
	FILE* stream=NULL;
	char filename[100];
	void (*fp)(int noeq, double h, double t, double *y,
		   void (*dgl_rs) (int, double ,double *, double*),int call);
	fp=RK4;
	for(int i=0;i<3;i++){
		if(i==0){
			y_0=1;
			v_0=0;
		}
		if(i==1){
			y_0=0;
			v_0=1;
		}
		if(i==2){
			y_0=0.5;
			v_0=0.5;
		}
		h=0.1;
		
		for(int j=0;j<4;j++){
			sprintf(filename,"data/ueb5_%d_%d",i,j);
			stream=fopen(filename,"w");
			for(int k=0;k<4;k++){
				if(k==0){
					fp=euler_cauchy;
				}
				if(k==1){
					fp=trapez;
				}
				if(k==2){
					fp=RK3;
				}
				if(k==3){
					fp=RK4;
				}
				first=1;
				y[0]=y_0;
				y[1]=v_0;
				tprint=t0;
				for(t=t0;t<=tend;t+=h){
					if(t>=tprint)  {
						exact=y_0*cos(t)+v_0*sin(t);         
						diff=fabs((exact-y[0])/exact);   
						fprintf(stream,"%le;",t);
						fprintf(stream,"%le;",exact);
						fprintf(stream,"%le;",y[0]);
						fprintf(stream,"%le\n",diff);
						//printf("   %20.5le %20.5le %20.5le %20.5le %20.5le %20.5le\n",
						//	   t,exact,y[0],diff,y_check[0],fabs((exact-y_check[0])/exact));
						tprint+=tstep;  
					}
					   
					fp (noeq,h,t,y,harm_osz,first );
					first=0;
				}
				//fprintf(stream,"   %20d;   %20d;   %20d;   %20d;\n",10,10,10,10);
				fp (noeq,h,t,y,harm_osz,-1 );
			}
			  
			h/=10;
			fclose (stream);
		}
		
		
	}*/
	mem_free_all ();
}//1e-4 0 1 0 10 1