#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "../generalmemorymanager/generalmemorymanager.h"
#include "../function_roots/function_roots.h"
#include "../numerov/numerov.h"


double omega;                               
double *y_loesung;                     
numerov_data_t maindat={.n=1};


double fs(double r){ 
	return -0.5*r*exp(-r); 
}
double fg(double r){ 
	return -omega*omega; 
}

double f_randbed(double para){                          
	numerovup(maindat,maindat.n-2,0,para, y_loesung);
	if(isnan(y_loesung[maindat.n-1]))
		y_loesung[maindat.n-1]=1e-300;
	return y_loesung[maindat.n-1];
}

double analyticalsol1(double r){
	return 0.125*r*(1+r)*exp(-r);
}

int main(){
	mem_init(0);
    double rmax,para,zero;  
    omega=1;
    printf("# Geben Sie rmax und die Anzahl der Stuetzstellen ein:");
    int ret=scanf(" %le %d",&rmax,&(maindat.n));
	
    maindat.r=mem_alloc(maindat.n*sizeof(double));   /* alloziere Speicher fuer r, g und s */ 
    maindat.g=mem_alloc(maindat.n*sizeof(double));
    maindat.s=mem_alloc(maindat.n*sizeof(double));
    y_loesung=mem_alloc(maindat.n*sizeof(double));

    init_numerov(0.0,rmax,&maindat,fg,fs); 
	printf ("#%d, h=%e\n",ret,maindat.h); 

    para=rootsecant(1.0, 2.0, &f_randbed,1e-12);
	//check:
    zero=f_randbed(para);
    
    printf("# %15s %15s %15s \n","r","Phi","analphi");
	FILE* mystream1=fopen("data/ueb6_1_1.dat","w");
	double exact;
    for(int i=1; i<maindat.n; i++)
      {
		exact=analyticalsol1 (maindat.r[i]);
       fprintf(mystream1," %15.6e %15.6e %15.6e %15.6e \n",maindat.r[i],
			   y_loesung[i],exact,fabs (y_loesung[i]-exact)); 
      }
    printf("#Parameter, Null und Schrittweite: %15.12e %15.6e %15.6e\n",para,
		   zero,maindat.h);
	fclose (mystream1);
    mem_free_all ();
    return EXIT_SUCCESS;
  }