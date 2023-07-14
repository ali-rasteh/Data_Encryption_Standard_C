#include "includes.h"

/*
This function creates the main key and prints it. After the main key is created we are ready to
create the iteration keys using them. Also here we print the key so we can se the value.
*/
void make_main_key(unsigned char* main_key) {
	int i;
	for (i=0; i<8; i++) {
		main_key[i] = (unsigned char)(0x5C);
	}

	printf("The main key is : ");
	for (i=0; i<8; i++) {
		print_binary_value(main_key[i]);
	} 
	printf("\n");
}

void fill_input_text(unsigned char* input_text)
{
	int i;
	for (i=0; i<8; i++) {
		input_text[i] = (unsigned char)(0xAA);
	}
	printf("The inupt text is : ");
	for (i=0; i<8; i++) {
		print_binary_value(input_text[i]);
	} 
	printf("\n");
}

int main() {

	// Defining needed variables
	int i;
	clock_t start, end;
	double execution_time;
	unsigned int iseed = (unsigned int)time(NULL);
	short int operation_mode;
	// Definign and allocating memory for the main pointers needed for our work
	unsigned char* cryp_main_key = (unsigned char*) malloc(8*sizeof(char));
	unsigned char* input_text = (unsigned char*) malloc(8*sizeof(char));
	unsigned char* output_text = (unsigned char*) malloc(8*sizeof(char));
	iteration_key* iteration_keys = (iteration_key*)malloc(17*sizeof(iteration_key));

	// Creating a random value and making the main key for producing the other keys from that
	srand (iseed);
	make_main_key(cryp_main_key);
	fill_input_text(input_text);


	// Making iteration keys and estimating the time taken for creating these keys
	start = clock();
	make_iteration_keys(cryp_main_key, iteration_keys);
	end = clock();
	execution_time = 1000000*(double)(end - start)/(double)CLOCKS_PER_SEC;
	printf("Making iterations key execution time : %1f microseconds.\n", execution_time);

	// Doing the main encryption and decryption operations and estimating the time taken for execution
	start = clock();
	enc_dec_input_text(input_text, iteration_keys, MODE_ENCRYPTION, output_text);
	end = clock();
	execution_time = 1000000*(double)(end - start)/(double)CLOCKS_PER_SEC;
	printf("Encryption/decryption execution time : %1f microseconds.\n", execution_time);
	
	printf("The output text is : ");
	for (i=0; i<8; i++) {
		print_binary_value(output_text[i]);
	} 
	printf("\n");

	// Freeing the memory allocated while defining the variables for preventing memory leakage
	free(cryp_main_key);
	free(input_text);
	free(output_text);
	free(iteration_keys);

	return 0;
}
