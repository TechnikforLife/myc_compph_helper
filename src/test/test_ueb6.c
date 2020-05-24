#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "../generalmemorymanager/generalmemorymanager.h"
#include "../numerov/numerov.h"
#include "../function_roots/function_roots.h"


double omega=1;                               
double *y_loesung;                     
numerov_data_t maindat={.n=1};

double parafinder(double a,double b,double (*fp)(double,int*),double precision){
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
	double fpi,fpim1,fpip1;
	int info=0;
	int w1=0,w2=0;
	double abc=1e-7;//pow(maindat.n,-1.5);
	/**
	 * @note	Try to estimate the root of "fp" with the given startvalues
	 * 			and to the given precision.
	 */
	for(i=0;i<10000;i++){
		fpim1=fp(x_im1,&info);
		if(info)w1=1;
		fpi=fp(x_i,&info);
		if(info)w2=1;
		if(w1||w2){
			x_ip1=(x_i+x_im1)/2;
			fpip1=fp(x_ip1,&info);
			if (fabs(fpip1)<0.1)return x_ip1;
			if(fpip1==0)return x_ip1;
			if(fpim1*fpip1<0){
				x_i=x_ip1;
			}else if(fpi*fpip1<0){
				x_im1=x_ip1;
			}
			printf("%25.20e %25.20e\n",x_i,x_im1-x_i);
			
		}else{
			x_ip1=x_i+(fpi*(x_im1-x_i))/(fpi-fpim1);
			printf("b\n");
			x_im1=x_i;
			x_i=x_ip1;
		}
		if(fabs(x_im1-x_i)<precision*fabs(x_i)){
			break;
		}
		
		
		w1=0;
		w2=0;
		
		
		//printf ("%d %30.20e %30.20e %30.20e\n",i,x_ip1,fp(x_i),fp(x_im1));
	}
	if(i==10000){
		printf("[WARNING] Could not reach given precision!\n");
	}
	return x_ip1;
}
double fs(double r){ 
	return -0.5*r*exp(-r); 
}
double fg(double r){ 
	return -omega*omega; 
}

double f_randbed(double para,int* info){                          
	numerovup(maindat,maindat.n-2,0,para, y_loesung);
	int i=0;
	for(;i<maindat.n;i++){
		if(i*maindat.h>10)break;
	}
	for(;i<maindat.n;i++){
		if(fabs(y_loesung[i])>0.1){
			*info=1;
			return y_loesung[maindat.n-1];
		}
	}
	*info=0;
	return y_loesung[maindat.n-1];
}


double f_rand(double para){                          
	numerovup(maindat,maindat.n-2,0,para, y_loesung);
	return y_loesung[maindat.n-1];
}

double analyticalsol1(double r){
	return 0.125*r*(1+r)*exp(-r);
}

void jacobi(double *u,numerov_data_t dat){//1581
	double temp1,temp2;
	temp1=u[0];
	for(int i=1;i<dat.n-1;i++){
		temp2=temp1;
		temp1=u[i];
		u[i]=(u[i+1]+temp2-dat.h*dat.h*dat.s[i])/(2-dat.h*dat.h*dat.g[i]);
	}
}

void gaussseidel(double *u,numerov_data_t dat){//813
	for(int i=1;i<dat.n-1;i++){
		u[i]=(u[i+1]+u[i-1]-dat.h*dat.h*dat.s[i])/(2-dat.h*dat.h*dat.g[i]);
	}
}

void relax(double *u,numerov_data_t dat,double R){
	// r=0.5:2311
	// r=1.0:813
	// r=1.5:278
	// r=1.9:76
	// r=1.95:196
	// r=1.99:893
	for(int i=1;i<dat.n-1;i++){
		u[i]=(1-R)*u[i]+R*(u[i+1]+u[i-1]-dat.h*dat.h*dat.s[i])/(2-dat.h*dat.h*dat.g[i]);
	}
}

double functional_E(double* u,numerov_data_t dat){
	double ret=0;
	for(int i=1;i<dat.n;i++){
		ret+=(u[i]-u[i-1])*(u[i]-u[i-1])/(2*dat.h*dat.h)-dat.g[i]*u[i]*u[i]/2.
				+dat.s[i]*u[i];
	}
	return ret*dat.h;
}

int main(){
	mem_init(0);
    double rmax,para,zero=10;
	int n;  
    omega=1;
    printf("# Geben Sie rmax und die Anzahl der Stuetzstellen ein:");
    int ret=scanf(" %le %d",&rmax,&n);
	rmax*=10;
	maindat.n=(n-1)*10+1;
    maindat.r=mem_alloc(maindat.n*sizeof(double));  
    maindat.g=mem_alloc(maindat.n*sizeof(double));
    maindat.s=mem_alloc(maindat.n*sizeof(double));
    y_loesung=mem_alloc(maindat.n*sizeof(double));

    init_ittertable(0.0,rmax,&maindat,fg,fs); 
	maindat.n=10/maindat.h+1;
	para=rootsecant(0, 1, &f_rand,1e-12);
	printf("#Parameter, Null und Schrittweite: %15.12e %15.6e %15.6e\n",para,
		   zero,maindat.h);
	for(double j=10;j<=rmax;j+=10){
		maindat.n=j/maindat.h+1;
		para=parafinder (para*0.8, para*1.2, &f_randbed,1e-12);
	}
	maindat.n=n;  
    //para=parafinder(para*0.9, para*1.1, &f_randbed,1e-12);
	//check:
	int info=0;
    zero=f_randbed(para,&info);
    printf ("#%d, h=%e, info=%d\n",ret,maindat.h,info); 
    printf("# %15s %15s %15s \n","r","Phi","analphi");
	FILE* mystream1=fopen("data/ueb6_1_1.dat","w");
	double exact;
    for(int i=1; i<n; i++){
		exact=analyticalsol1 (maindat.r[i]);
       fprintf(mystream1," %15.6e %15.6e %15.6e %15.6e \n",maindat.r[i],
			   y_loesung[i],exact,fabs (y_loesung[i]-exact)); 
      }
    printf("#Parameter, Null und Schrittweite: %15.12e %15.6e %15.6e\n",para,
		   zero,maindat.h);
	fclose (mystream1);
	mem_free_all ();
	////////////////////////////////////////////////////////////////////////
	// Part 2:
	mem_init (0);
	printf("///////////////////////////////////////////////////////////////////"
			"//////////////////////////////////////////////////////////////\n");
	double b=20,eps;
	omega=1;
	maindat.n=200;
	double* uk;
	uk=(double*)mem_alloc(maindat.n*sizeof (double));
	maindat.g=(double*)mem_alloc(maindat.n*sizeof (double));
	maindat.s=(double*)mem_alloc(maindat.n*sizeof (double));
	maindat.h=(b-0)/(maindat.n-1);
	for(int i=0;i<maindat.n;i++){
		uk[i]=0;
		maindat.g[i]=fg(0+i*maindat.h);
		maindat.s[i]=fs(0+i*maindat.h);
	}
	double Ek,Ekp1;
	FILE* mystream2=fopen("data/ueb6_2_2.dat","w");
	Ek=functional_E (uk, maindat);
	int j;
	for(j=0;j<10000;j++){
		//for(int j=0;j<maindat.n;j++){
			//printf ("%10.5e;",uk[j]);
			//if(!j%5)printf("\n");
		//}
		//printf("\n");
		relax(uk,maindat,1.99);
		Ekp1=functional_E (uk, maindat);
		fprintf(mystream2,"%e\t%e\n",log(j+1),Ekp1);
		eps=fabs((Ekp1-Ek)/Ekp1);
		Ek=Ekp1;
		if(eps<1e-10)break;
	}
	printf("j=%d\n",j);
	mystream1=fopen("data/ueb6_2_1.dat","w");
	double x=0;
	for(int j=0;j<maindat.n;j++){
		x=0+j*maindat.h;
		fprintf (mystream1,"%e\t%e\t%e\n",x,uk[j],analyticalsol1(x));
	}
	fclose(mystream1);
	fclose(mystream2);
    mem_free_all ();
    return EXIT_SUCCESS;
  }