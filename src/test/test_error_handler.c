#include "../generalmemorymanager/generalmemorymanager.h"
#include "../error_handler/error_handler.h"

int main (int argc, char *argv[]){
	mem_init();
	double* abc=mem_alloc (sizeof(double)*10);
	double* def=mem_realloc (abc, sizeof(double)*20);
	printf ("Hello, World!\n%p\n%p\n%ld,%ld\n",(void*)abc,(void*)def,
			sizeof(double),sizeof (void*));
	mem_free (def);
	abc=mem_alloc (sizeof(double)*10);
	def=mem_alloc (sizeof(double)*20);
	mem_free_all ();
	mem_init();
	abc=mem_alloc (sizeof(double)*10);
	def=mem_realloc (abc, sizeof(double)*20);
	printf ("Hello, World!\n%p\n%p\n%ld,%ld\n",(void*)abc,(void*)def,
			sizeof(double),sizeof (void*));
	mem_free (def);
	abc=mem_alloc (sizeof(double)*10);
	def=mem_alloc (sizeof(double)*20);
	fatal_error(1,"Ups",42,__func__,__FILE__,__LINE__);
	mem_free_all ();
	
	return EXIT_SUCCESS;
}
