// Defining headergaurd
#ifndef _DES_H_
#define _DES_H_

// Include anything needed
#include "includes.h"

// Defining the constant bit size values
#define text_size_bits 64
#define expansion_size_bits 48
#define main_key_size_bits 56
#define compressed_key_size_bits 48

// Defining the operation modes
#define MODE_ENCRYPTION 1
#define MODE_DECRYPTION 0

// Defining the number of iterations for encryption and decryption
#define iterations_num 16


// This structure contains the key information for each iteration
typedef struct {
	unsigned char key[8];
	unsigned char temp1[4];
	unsigned char temp2[4];
} iteration_key;


// Declaration of the functions in des.c
void make_iteration_keys(unsigned char* main_key, iteration_key* iteration_keys);
void permute(unsigned char* input, unsigned char* output, int* permutation, int input_size_bits);
void enc_dec_input_text(unsigned char* input_text, iteration_key* iteration_keys, int mode, unsigned char* output_text);

#endif
