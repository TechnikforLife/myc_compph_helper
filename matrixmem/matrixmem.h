#ifndef MATRIXMEM_H
#define MATRIXMEM_H
typedef struct matrix{
	double ** data;
	int h_len;
	int v_len;	
}matrix_t;

int** matrix_alloc_integer(const int);
void matrix_free_integer(int**);
void matrix_print_integer(int** , const int );

matrix_t* matrix_alloc_double(const int ,const int );
matrix_t* matrix_quad_alloc_double(const int);
void matrix_free_double(matrix_t*);
matrix_t* createrotationmatrix(const double );
void matrix_print_double(matrix_t*);
matrix_t* matrix_id_double(matrix_t*);

matrix_t* matrix_quad_transpose(matrix_t*);
matrix_t* matrix_transpose(matrix_t*);

matrix_t* matrix_quad_multiply(matrix_t*,matrix_t*);
matrix_t* matrix_multiply(matrix_t*,matrix_t*);
/*#define matrix_free(x) _Generic ((x),\
	double**:matrix_free_double,\
	int**:matrix_free_integer)(x)
#define matrix_print(x,n) _Generic ((x),\
	double**:matrix_print_double,\
	int**:matrix_print_integer)(x,n)*/
#endif //ifndef MATRIXMEM_H