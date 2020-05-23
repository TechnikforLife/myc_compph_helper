#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "../generalmemorymanager/generalmemorymanager.h"
#include "../function_roots/function_roots.h"

/* Code fuer die Loesung der Poisson-Gleichung mit gaussfoermiger Ladungsverteilung */

/* wegen Nullstellensuche definiere globale Felder, die in 
   Funktion zur Nullstellensuche genutzt werden koennen */

double r0bound,omega;                               /* definiert radius der homogenen Ladungsverteilung */
double *r_array,*g_array,*s_array,*y_loesung; /* Zeiger auf Felder fuer Numerov und Loesung */
double schrittweite_h;                        /* benutzte Schrittweite */
int num_r;                                    /* Anzahl der Stuetzstellen */ 

double gfunc(double r)
/* zu loesende Gleichung: y''(r)+g(r)*y(r)=s(r) 
   hier Definition der Funktion g(r)   */
  {
    return 0.0;      
  }

double sfunc(double r)
// zu loesende Gleichung: y''(r)+g(r)*y(r)=s(r) 
// hier Definition der Funktion s(r)   
  {
    
    return -4.0*r*M_PI*exp(-(r/r0bound)*(r/r0bound))/(r0bound*r0bound*r0bound*sqrt(M_PI*M_PI*M_PI)); 
  }


double fs(double r)
// zu loesende Gleichung: y''(r)+g(r)*y(r)=s(r) 
// hier Definition der Funktion s(r)
{
    
	return -0.5*r*exp(-r); 
}
double fg(double r)
// zu loesende Gleichung: y''(r)+g(r)*y(r)=s(r) 
// hier Definition der Funktion s(r)   
{ 
	return -omega*omega; 
}



double init_numerov(double a,double b,int n,double *r,double *g,double *s)
/* Funktionen bereitet Anwendung des Numerov Verfahrens vor 
   a,b,n sind Intervallgrenzen und Anzahl der Stuetzstellen 
   bei Verlassen der Routine beinhalten die Felder r,g und s 
   Stuetzstellen, Funktion g an den Stuetzstellen und s an den Stuetzstellen
   Rueckgabewert ist die Schrittweite h */
  {
   int i;
   double h;
   
   h=(b-a)/(n-1);                /* bestimme Intervalllaenge */
   for(i=0; i<n; i++)            /* belege die Felder mit den Werten fuer r,g und s*/
     {
       r[i]=a+i*h;
       g[i]=fg(r[i]);
       s[i]=fs(r[i]);
     }
   
   return h;  /* Rueckgabewert ist Schrittweite h */ 
  }  


void numerovup(double *r,double *g,double *s,double h,int n,int steps,double y0,double y1,double *y)
/* Funktion nutzt das Numerov Verfahren um fuer gegebene Stuetzstellen r
   und Funktionen g und s die Loesung y zu finden. 
   r, g und s sollten mit init_numerov vorbereitet werden
   h ist die Schrittweite (auch aus init_numerov)
   n ist die Anzahl der Stuetzstellen 
   steps legt fest, wieviele Numerovschritte ausgefuehrt werden
   y0 und y1 sind die Startwerte y[0] und y[1], die Routine legt dann y[2] .. y[steps+1] fest 
   y ist ein Feld der Laenge  steps+2, das die Loesung bei Rueckkehr enthaelt
*/
 {
   int i;
   double fakt_u_np1,fakt_u_n,fakt_u_nm1; /* Variablen fuer Numerov Faktoren */ 
   double fakt_s;    

   y[0]=y0;  /* belege erste Funktionswerte mit den Startwerten  */
   y[1]=y1;
   
   for(i=1; i<steps+1; i++)   /* betrachte in den Schritten y(i-1) und y(i) um y(i+1) zu berechnen */
     {
       fakt_u_np1=1.0+h*h*g[i+1]/12.;     
       fakt_u_n=1.0-5.*h*h*g[i]/12.;      
       fakt_u_nm1=1.0+h*h*g[i-1]/12.;
       fakt_s=h*h/12.0*(s[i+1]+10.0*s[i]+s[i-1]);   /* Faktor mit s */
       
       y[i+1]=(fakt_s+2.0*fakt_u_n*y[i]-fakt_u_nm1*y[i-1])/fakt_u_np1; /* Vorwaertsiteration */ 
		if(fabs(y[i+1]-y[i])>fabs (y[i])&&i*h>10){
			y[i+1]=y[i]*0.9;
		}  
     }
   
 }

void numerovdown(double *r,double *g,double *s,double h,int n,int steps,double yn,double ynm1,double *y)
/* Funktion nutzt das Numerov Verfahren um fuer gegebene Stuetzstellen r
   und Funktionen g und s die Loesung y zu finden. 
   r, g und s sollten mit init_numerov vorbereitet werden
   h ist die Schrittweite (auch aus init_numerov)
   n ist die Anzahl der Stuetzstellen 
   steps legt fest, wieviele Numerovschritte ausgefuehrt werden
   yn und ynm1 sind die Startwerte y[n-1] und y[n-2], die Routine legt dann y[n-3] .. y[n-steps-2] fest 
   y ist ein Feld der Länge n, das die Loesungen
*/
 {
   int i;
   double fakt_u_np1,fakt_u_n,fakt_u_nm1; /* Variablen fuer Numerov Faktoren */ 
   double fakt_s;    

   y[n-1]=yn;  /* belege erste Funktionswerte mit den Startwerten  */
   y[n-2]=ynm1;
   
   for(i=n-2; i>n-steps-2; i--)   /* betrachte in den Schritten y(i-1) und y(i) um y(i+1) zu berechnen */
     {
       fakt_u_np1=1.0+h*h*g[i+1]/12.;     
       fakt_u_n=1.0-5.*h*h*g[i]/12.;      
       fakt_u_nm1=1.0+h*h*g[i-1]/12.;
       fakt_s=h*h/12.0*(s[i+1]+10.0*s[i]+s[i-1]);   /* Faktor mit s */
       
       y[i-1]=(fakt_s+2.0*fakt_u_n*y[i]-fakt_u_np1*y[i+1])/fakt_u_nm1; /* Rueckwaertsiteration */   
     }

 }
  
double f_randbed(double para)
/* Nullstelle dieser Funktion signalisiert, dass die Loesung 
   konsistent mit der Randbedinung ist
   para ist der freie Parameter der Loesung 
   hier: para ist der Konstantewert der Loesung bei großen r 
   Die Funktion nutzt globale Variabeln, um die Felder 
   r, g, s, h und n zu erhalten   
   und feld y_loesung fuer die Loesung */  
{                          
  numerovup(r_array,g_array,s_array,schrittweite_h,num_r,num_r-2,0,para,y_loesung);
	if(isnan(y_loesung[num_r-1]))
		y_loesung[num_r-1]=1e-300;
	return y_loesung[num_r-1];  /* zweite Randbedingung ist y[0] = 0 */
}

double analyticalsol1(double r){
	return 0.125*r*(1+r)*exp(-r);
}
int main(){
	mem_init(0);
    double rmax,para,zero;  /* maximales r und konsistente Randbedingung und Null aus Auswertung der Randbedingungsfunktion */ 
    //double rho;  /* fuer Ausgabe der Ladungsverteilung */
    omega=1;
    printf("# Geben Sie rmax und die Anzahl der Stuetzstellen ein:");
    int ret=scanf(" %le %d",&rmax,&num_r);
	
    r_array=mem_alloc(num_r*sizeof(double));   /* alloziere Speicher fuer r, g und s */ 
    g_array=mem_alloc(num_r*sizeof(double));
    s_array=mem_alloc(num_r*sizeof(double));
    y_loesung=mem_alloc(num_r*sizeof(double));

    schrittweite_h=init_numerov(0.0,rmax,num_r,r_array,g_array,s_array);  /* belege r,g und s mit Werten*/
	printf ("#%d, h=%e\n",ret,schrittweite_h);
    /* suche mit dem Schiessverfahren und mit Numerov die Loesung, die den Randbedingungen genuegt. */ 

    para=rootsecant(1.249937914618e-03, 2.0, &f_randbed,1e-12);
	//check:
    zero=f_randbed(para);
    
    printf("# %15s %15s %15s \n","r","Phi","analphi");
	FILE* mystream1=fopen("data/ueb6_1_1.dat","w");
	double exact;
    for(int i=1; i<num_r; i++)
      {
		exact=analyticalsol1 (r_array[i]);
       fprintf(mystream1," %15.6e %15.6e %15.6e %15.6e \n",r_array[i],y_loesung[i],exact,fabs (y_loesung[i]-exact)); 
      }

    printf("#Parameter, Null und Schrittweite: %15.12e %15.6e %15.6e\n",para,zero,schrittweite_h);
	fclose (mystream1);
    mem_free_all ();
    return EXIT_SUCCESS;
  }