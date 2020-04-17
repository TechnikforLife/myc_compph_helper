#include <stdio.h>
#include <stdlib.h>
#include "matrixmem.h"
#include <math.h>
//d=dimension
//sd=spacedimenion
/*
1	0	0
0	1	0
0	0	1
has d=2,sd=3

*/
int** matrix_alloc_integer(/*number of space dimension=length of each dimension*/	const int dimlen){
	int * ptr2matrixdata_mem=(int*)malloc(sizeof(int)*dimlen*dimlen);
	int ** ptr2matrixdata=(int**)malloc(sizeof(int*)*dimlen);
	if(ptr2matrixdata_mem==NULL||ptr2matrixdata==NULL){
		return NULL;
	}
	for(unsigned int i=0;i<dimlen;++i){
		ptr2matrixdata[i]=ptr2matrixdata_mem+dimlen*i;
	}
	return ptr2matrixdata;

}
void matrix_free_integer(/*pointer to matrix to free*/	int** ptr2matrixdata){
	free(ptr2matrixdata[0]);
	free(ptr2matrixdata);

}
void matrix_print_integer(/*pointer to matrix to print*/							int** ptr2matrixdata,
						/*number of space dimension=length of each dimension*/		const int dimlen){
	for(int i = 0; i < dimlen; ++i){
		printf("|");
		for(int j = 0; j < dimlen; ++j){
			printf("%5d ", ptr2matrixdata[i][j]);
		}
		printf("|\n");
	}
}



matrix_t* matrix_alloc_double(
	/*vertical length*/		const int v_len,
	/*hrizontal length*/	const int h_len){
	matrix_t* ptr2matrix=NULL;
	double** ptr2matrixdata = NULL;
	double* ptr2matrixdata_mem = NULL;
	//RAM allocation:
	ptr2matrix=(matrix_t*)malloc(sizeof(matrix_t));
	ptr2matrixdata = (double**)malloc(sizeof(double*) * v_len);
	ptr2matrixdata_mem=(double*)malloc(sizeof(double)*v_len*h_len);
	if(ptr2matrixdata_mem==NULL||ptr2matrixdata==NULL||ptr2matrix==NULL){
		return NULL;
	}
	for(unsigned int i=0;i<v_len;++i){
		ptr2matrixdata[i]=ptr2matrixdata_mem+h_len*i;
		//ptr to each new row is declared
	}
	ptr2matrix->h_len=h_len;
	ptr2matrix->v_len=v_len;
	ptr2matrix->data=ptr2matrixdata;
	return ptr2matrix;
}

matrix_t* matrix_quad_alloc_double(
	/* length of both dimensions*/const int dimlen){
	return matrix_alloc_double(dimlen,dimlen);
}

void matrix_free_double(/*pointer to matrix to free*/	matrix_t* ptr2matrix){
	free(ptr2matrix->data[0]);
	free(ptr2matrix->data);
	free(ptr2matrix);

}

matrix_t* createrotationmatrix(/*angle to rotate by*/	const double angle){
	matrix_t* rotationmatrix = NULL;
	//Ram allocation:
	rotationmatrix = matrix_quad_alloc_double(2);
	if(rotationmatrix == NULL){
		printf("Error in RAM allocation\n");
		return NULL;
	}
	//setting of the values:
	rotationmatrix->data[0][0] = cos(angle);
	rotationmatrix->data[0][1] = sin(angle);
	rotationmatrix->data[1][0] = -sin(angle);
	rotationmatrix->data[1][1] = cos(angle);
	return rotationmatrix;
}

void matrix_print_double(/*pointer to matrix to print*/	matrix_t* ptr2matrix){
	for(int i = 0; i < ptr2matrix->v_len; ++i){
		printf("|");
		for(int j = 0; j < ptr2matrix->h_len; ++j){
			printf("%15e ", ptr2matrix->data[i][j]);
		}
		printf("|\n");
	}
	printf("\n");

}


matrix_t* matrix_id_double(
	/*matrix to initialize
	as unitmatrix*/		matrix_t* ptr2matrix){
		int len=0;
	if(ptr2matrix->h_len!=ptr2matrix->v_len){
		printf("[INFO]:Using non quadratic matrix!\n");
		//use shorter side length to get a quadratic sub matrix of ptr2matrix
		len=((ptr2matrix->h_len)<(ptr2matrix->v_len))?ptr2matrix->h_len:ptr2matrix->v_len;
	}else{
		len=ptr2matrix->h_len;
	}
	for(int i=0;i<len;++i){
		for(int j=0;j<len;++j){
			ptr2matrix->data[i][j]=(i==j)?1.:0.; //i=j-> data[i][j]=1
		}
	}
	return ptr2matrix;
}

matrix_t* matrix_quad_transpose(/*quadratic matrix to transpose*/	matrix_t* ptr2matrix){
	double temp=0.;
	for(int i = 0; i < ptr2matrix->v_len; ++i){
		for(int j = 0; j < i; ++j){
			temp=ptr2matrix->data[i][j];
			ptr2matrix->data[i][j]=ptr2matrix->data[j][i];
			ptr2matrix->data[j][i]=temp;
		}
	}
	return ptr2matrix;
}
//Todo add functions for non quadratic matrix!

matrix_t* matrix_transpose(/*matrix to transpose*/	matrix_t* ptr2matrix){
	if(ptr2matrix->h_len==ptr2matrix->v_len){
		return matrix_quad_transpose(ptr2matrix);
	}
	return ptr2matrix;
}

matrix_t* matrix_quad_multiply(/*first quadratic matrix*/	matrix_t* A,
						/*second quadratic matrix*/			matrix_t* B){
	//A*B=C (Matrixmultiplication)
	if(A->h_len!=B->v_len){
		printf("Can not multiply %d x %d -Matrix with %d x %d -Matrix",\
			A->v_len,A->h_len,B->v_len,B->h_len);
		return NULL;
	}
	matrix_t* C=NULL;
	C=matrix_quad_alloc_double(A->h_len);
	if(C==NULL){
		return NULL;
	}
	double sum=0.;
	for(int i=0;i<C->v_len;++i){
		for(int j=0;j<C->h_len;++j){
			for(int k=0;k<A->h_len;++k){
				sum+=(A->data[i][k])*(B->data[k][j]);
			}
			C->data[i][j]=sum;
			sum=0.;
		}

	}

	return C;
}

matrix_t* matrix_multiply(/*first matrix*/	matrix_t* A,
						/*second matrix*/	matrix_t* B){
	//A*B=C (Matrixmultiplication)
	if(A->h_len!=B->v_len){
		printf("Can not multiply %d x %d -Matrix with %d x %d -Matrix",\
			A->v_len,A->h_len,B->v_len,B->h_len);
		return NULL;
	}
	if((A->h_len==A->v_len)&&(B->h_len==B->v_len)){
		return matrix_quad_multiply(A,B);
	}
	return B;
}


