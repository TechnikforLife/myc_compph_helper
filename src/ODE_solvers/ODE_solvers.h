/** 
 *  @file ODE_solvers.h 
 *  @brief Provides functions to solve equations
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 30.03.2020  	First Implementation of:
 *						squaresolv
 * 
 *  @todo Implement other functions (complex)
 * 
 *  @todo Implement own type for return objects
 *
 *  @test test complex functionality
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1   
 */
 
#ifndef ODE_SOLVERS_H
#define ODE_SOLVERS_H
/**
 * @fn void fatal_error(const int condition,const char* message, const int errorcode,const char * fct);
 * @brief Function to solve a quadtratic equation
 *
 * This function calculates the real solutions for the equation:
 * abc[0]*x^2+abc[1]*x+abc[2]=0
 *
 * @param abc Pointer to double array countaining the values of parameters a,b and c
 * @param sol Pointer to the array to save the solutions into
 *
 * @return Amount of solutions found (-1 if infinitly many)
 */
double* y_check;
int bindex(int q,int r);

void rk_mem_alloc(double**a,double**b,double**c,double**k,double**yh,int p,int noeq);

void rk_mem_free(double*a,double*b,double*c,double*k,double*yh,int p);

void euler_cauchy(int noeq, double h, double t, double *y,
		   void (*dgl_rs) (int, double ,double *, double*),int initialcall);

void trapez(int noeq, double h, double t, double *y,
		   void (*dgl_rs) (int, double ,double *, double*),int call);

void RK3(int noeq, double h, double t, double *y,
		   void (*dgl_rs) (int, double ,double *, double*),int call);

void RK4(int noeq, double h, double t, double *y,
		   void (*dgl_rs) (int, double ,double *, double*),int call);

void runge_kutta(int noeq,double h, double t,double *y,
				 void (*dgl_rs) (int, double ,double *, double*),
				 int p,double* a,double* b,double* c,double* k,double* yh);
#endif //ifndef ODE_SOLVERS_H