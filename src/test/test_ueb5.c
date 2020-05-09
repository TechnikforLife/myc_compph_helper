#include "../generalmemorymanager/generalmemorymanager.h"
#include "../ODE_solvers/ODE_solvers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
void harm_osz(int noeq,double t,double* y,double* f){
	if(noeq!=2){
		fprintf (stderr,"The amoun of equations is not fitting!");
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
	double exact,diff=10;    /* Variablen, um Ergebnis zu speichern und vergleichen*/  
	double *y;         /* Zeiger auf Speicherplaetze, die double enthalten */

	double t,tprint; 
	double*f,*k1,*k2,*k3;
	/* Eingabe der Parameter */ 
	printf("Bitte geben Sie h,t0,y_0,v_0,tend und tstep ein: \n");
	scanf(" %le %le %le %le %le %le",&h,&t0,&y_0,&v_0,&tend,&tstep);  
	
	/* malloc reserviert Speicher fuer Feld mit y Werten und Hilfsfeld */ 
	y=mem_alloc(sizeof(double)*noeq);
	
	y_check=mem_alloc(sizeof(double)*noeq);     
	f=mem_alloc(sizeof(double)*noeq); 
	k1=mem_alloc(sizeof(double)*noeq);   
	k2=mem_alloc(sizeof(double)*noeq);   
	k3=mem_alloc(sizeof(double)*noeq);   
	    

	printf("\n   %20s %20s %20s %20s \n","t","exact","RK3","diff");
 
	y[0]=y_0;
	y[1]=v_0;
	y_check[0]=y_0;
	y_check[1]=v_0;
	tprint=t0;
	int first=1;
	for(t=t0;t<=tend;t+=h){
		
		if(t>=tprint) /* Naechsten Ausgabepunkt erreicht?*/ {
			exact=y_0*cos(t)+v_0*sin(t);           /* known exact value */ 
			diff=fabs((exact-y[0]));   /* and rel. error */
			printf("   %20.5le",t);
			printf("   %20.5le",exact);
			printf("   %20.5le",y[0]);
			printf("   %20.5le",diff);
			printf("   %20.5le",y_check[0]);
			printf("   %20.5le\n",fabs((exact-y_check[0])));
			//printf("   %20.5le %20.5le %20.5le %20.5le %20.5le %20.5le\n",
			//	   t,exact,y[0],diff,y_check[0],fabs((exact-y_check[0])/exact));
			tprint+=tstep;  /* Ausgabe und naechsten Punkt bestimmen */
		}
 		     
		/* Dgl.schritt ausfuehren */ 
		      
		RK3 (noeq,h,t,y,harm_osz,first );
		RuKu_3(noeq,h,t,y_check,f,k1,k2,k3,harm_osz);
		first=0;
	}    
	mem_free_all ();
}//1e-4 0 1 0 10 1