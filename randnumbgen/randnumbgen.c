/** 
 *  @file randnumbgen.c
 *  @brief Provides functions to generate pseudorandom numbers
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 5.04.2020  	First Implementation of:
 *						randgenLehmerlongrange,Lehmer0_1trafo
 *						
 * 
 *  @todo at static to state
 * 
 *  @test compare to gsl
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1   
 */

int* randgenLehmerlongrange(/*current state in chain*/	int* state){
	//needed constants
	const int a=16807;
	const int m=2147483647;
	const int r=2836;
	const int q=127773;
	
	//calculate the pseudorandom number
	int temp=a*(*state%q)-r*(*state/q);
	if(temp<=0){
		temp+=m;
	}
	//save the pseudorandom number
	*state=temp;
	return state;
}

void Lehmer0_1trafo(/*current state in normal int chain*/	int * integerstate,
					/*current double state*/ 				double* state){
	//needed constants
	const int m=2147483647;
	
	//save the pseudorandom number
	*state =((double)*integerstate)/((double)m);
}