#include <math.h>
#include "integrate_trapez.h"
#include "../generalmemorymanager/generalmemorymanager.h"
#include <stdio.h>
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



double integratetrapez(double start,double end,double (*fp)(double*),
					   unsigned int n,double* variables,
					   double relprecision,int useprecision){
	/**
	 * Declarations:
	 * 
	 * @var intervalllength 	length of the complet interval
	 * @var subintervalllength	length of the subinterval
	 * @var sum					value of the sum
	 * @var f_x_i				f(x_i)
	 */
			
	double intervalllength=end-start;
	double subintervalllength=intervalllength/n;
	double sum=0.0;
	double f_x_i=0.0;
	
	/**
	 * @note	Calculate f(x_0) and at it to the sum with weight 0.5
	 */
	variables[0]=start;
	sum=(*fp)(variables)/2.;
	
	/**
	 * @note	Test rather the precision stop shoulb be used
	 * 			In either cases the f(x_i) i in [1,n-1] get calulated and 
	 * 			added to the sum.
	 * 			In case of using the precision stop:
	 * 				If the precision is reached the approximation 
	 * 				of the integral is returned
	 * 			At the end f(x_n) is being calculated and 
	 * 			added to the sum with weight 0.5
	 */
	if(useprecision){
		for(int i=1;i<n;i++){
			variables[0]=start+(i)*subintervalllength;
			f_x_i=(*fp)(variables);
			sum+=f_x_i;
			if(fabs(f_x_i)<fabs(sum*relprecision)){
				return sum*subintervalllength;
			}
		}
	}else{
		for(int i=1;i<n;i++){
			variables[0]=start+(i)*subintervalllength;
			f_x_i=(*fp)(variables);
			sum+=f_x_i;
		
			
		}
	}
	variables[0]=start+(n)*subintervalllength;
	sum+=(*fp)(variables)/2.;
	return sum*subintervalllength;
}

double integratetrapez_posinf(double lowerboundary,
					   double (*fp)(double*),double subintervalllength,
					   double* variables,double relprecision){
	/**
	 * Declarations:
	 * 
	 * @var i		itteration variable
	 * @var sum		value of the sum
	 * @var f_x_i	f(x_i)
	 */
	
	int i=1;
	double sum=0.0;
	double f_x_i=0.0;
	
	/**
	 * @note	Calculate f(x_0) and add it to the sum with weight 0.5
	 */
	variables[0]=lowerboundary;
	sum=(*fp)(variables)/2.;
	
	/**
	 * @note	f(x_i) gets calulated and added to the sum,
	 * 			until the f(x_i)<sum*relprecision.
	 */

	do{
		variables[0]=lowerboundary+subintervalllength*i;
		f_x_i=(*fp)(variables);
		sum+=f_x_i;
		i++;
		//printf("%e,%e,i=%d\n",f_x_i,sum,i);
	}while((fabs(f_x_i)>fabs(relprecision))||(fabs(f_x_i)>fabs(sum*relprecision)));
	//printf ("-\n");
	/**
	 * @note	Calculate f(x_n) (n last relevant index)
	 * 			and add it to the sum with weight 0.5
	 */
	variables[0]=lowerboundary+(i+1)*subintervalllength;
	sum+=(*fp)(variables)/2.;
	return sum*subintervalllength;
}

double convergeintegrate_homogenstepcount(double start,double end,
		double (*fp)(double*),double relprecision,
		const int startisminfty,const int endisinfty,double* variables){
	/**
	 * Declarations:
	 * @var oldb_steps	Saves the previous value of the integral 
	 * 					before optimization of the step count
	 * @var oldb_end	Saves the previous value of the integral 
	 * 					before optimization of the end boundary
	 * @var oldb_start	Saves the previous value of the integral 
	 * 					before optimization of the start boundary
	 * @var new			Saves the new value of the integral
	 * @var n			Step count
	 * @var tester		Needed to determine rather it is the first try 
	 * 					to change the boundaries
	 */
	double oldb_steps;
	double oldb_end;
	double oldb_start;
	double new;
	int n=10;
	int tester;
	
	/**
	 * Setting of start values:
	 * @note	If any boundary is infty the boundaries get changed and 
	 * 			the step count is increased appropriatly, 
	 * 			to stay at approximatly the same step size
	 */
	oldb_steps=integratetrapez(start,end,fp,n,variables,0.,0);
	oldb_end=oldb_steps;
	oldb_start=oldb_steps;
	if(endisinfty){
		end=fabs(end)*2;
		n+=(int)(end/2*n/(end/2-start))+1;
	}
	if(startisminfty){
		start=-fabs(start)*2;
		n+=(int)(end/2*n/(end/2-start))+1;
	}
	new=integratetrapez(start,end,fp,n,variables,0.,0);	//new value
	
	/**
	 * @note	If no boundary is infty,
	 * 			or the precision at the boundary is reached:
	 * 			Double the amount of Steps(=half the step size) 
	 * 			until the requested precision is reached.
	 * @note	If a boundary is infty:
	 * 			That boundary gets tested rather it needs to be changed, 
	 * 			if so the boundary gets changed and 
	 * 			the step count is increased appropriatly, 
	 * 			to stay at approximatly the same step size.
	 */
	do{
		if(endisinfty&&fabs(new-oldb_end)>fabs(relprecision*new)){
			oldb_end=new;
			tester=1;
			new=integratetrapez(start,end*2,fp,n*2,variables,0.,0);
			while(fabs(new-oldb_end)>fabs(relprecision*new)){
				oldb_end=new;
				if(tester){
					n+=(int)(end*n/(end-start))+1;
					end*=2;
					tester=0;
				}
				n+=(int)(end*n/(end-start))+1;
				end*=2;
				new=integratetrapez(start,end,fp,n,variables,0.,0);
			}
		}
		if(startisminfty&&fabs(new-oldb_start)>fabs(relprecision*new)){
			oldb_start=new;
			tester=1;
			new=integratetrapez(start*2,end,fp,n*2,variables,0.,0);
			while(fabs(new-oldb_start)>fabs(relprecision*new)){
				oldb_start=new;
				if(tester){
					n+=(int)(end*n/(end-start))+1;
					start*=2;
					tester=0;
				}
				n+=(int)(end*n/(end-start))+1;
				start*=2;
				new=integratetrapez(start,end,fp,n,variables,0.,0);
			}
		}
		oldb_steps=new;
		n*=2;
		new=integratetrapez(start,end,fp,n,variables,0.,0);
	}while(fabs(new-oldb_steps)>fabs(relprecision*new));
	return new;
}


double integrate_trapez_hd_cube(int dimensions,double lowerboundary,
								 double upperboundary,int n,
								 double (*fp)(double *,int dim)){
	double h;
	double* x;
	int* index;
	double sum=0.;
	double summand=0.;
	
	x=(double*)mem_alloc (dimensions*sizeof (double));
	index=(int*)mem_alloc (dimensions*sizeof (int));
	
	for(int i=0;i<dimensions;i++){
		index[i]=0;
		x[i]=lowerboundary;
	}
	h=(upperboundary-lowerboundary)/n;
	/*for(int i=0;i<=n;i++){
		x[0]=lowerboundary+i*h;
		for(int j=0;j<=n;j++){
			x[1]=lowerboundary+j*h;
			for(int k=0;k<=n;k++){
				x[2]=lowerboundary+k*h;
				summand=fp(x,3);
				//printf("1:%e\n",summand);
				if(i==0||i==n){
					summand/=2.;
				}
				if(j==0||j==n){
					summand/=2.;
				}
				if(k==0||k==n){
					summand/=2.;
				}
				
				sum+=summand;
				//printf("2:summand=%e,sum=%e\n",summand,sum);
			}
			
		}
		
	}*/
	
	dimstager (0,x,index,&dimensions,&summand,&sum,&n,&h,&lowerboundary,fp);
	return sum*pow (h, dimensions);
}


void dimstager(int stage,double* x,int* index,int* dim,double *summand,
				 double* sum, int* n,double* h,double *lowerboundary,
				 double (*fp)(double *,int dim)){
	//printf ("%d\n",stage);
	if(stage<(*dim-1)){
		for(index[stage]=0;index[stage]<=*n;index[stage]++){
			x[stage]=*lowerboundary+index[stage]**h;
			dimstager (stage+1, x, index, dim,summand,sum, n, h, lowerboundary,fp);
		}
	}else{
		for(index[stage]=0;index[stage]<=*n;index[stage]++){
			x[stage]=(*lowerboundary)+(*h)*((double)index[stage]);
			*summand=fp(x,*dim);
			for(int i=0;i<*dim;i++){
				if(index[i]==0||index[i]==*n){
					*summand/=2.;
				}
			}
			*sum+=*summand;
		}
	}
	
}