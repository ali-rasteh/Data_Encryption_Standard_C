#include "des.h"
#include "includes.h"


// Initial text permutation indices
int initial_text_permutation[] = {58, 50, 42, 34, 26, 18, 10, 2,
								  60, 52, 44, 36, 28, 20, 12, 4,
								  62, 54, 46, 38, 30, 22, 14, 6,
								  64, 56, 48, 40, 32, 24, 16, 8,
								  57, 49, 41, 33, 25, 17,  9, 1,
								  59, 51, 43, 35, 27, 19, 11, 3,
								  61, 53, 45, 37, 29, 21, 13, 5,
								  63, 55, 47, 39, 31, 23, 15, 7};

// Fianl text permutation indices
int final_text_permutation[] = {40,  8, 48, 16, 56, 24, 64, 32,
								39,  7, 47, 15, 55, 23, 63, 31,
								38,  6, 46, 14, 54, 22, 62, 30,
								37,  5, 45, 13, 53, 21, 61, 29,
								36,  4, 44, 12, 52, 20, 60, 28,
								35,  3, 43, 11, 51, 19, 59, 27,
								34,  2, 42, 10, 50, 18, 58, 26,
								33,  1, 41,  9, 49, 17, 57, 25};

// Initial main key permutation indices
int initial_key_permutaion[] = {57, 49,  41, 33,  25,  17,  9,  1,
								58, 50,  42, 34,  26,  18, 10,  2,
								59, 51,  43, 35,  27,  19, 11,  3,
								60, 52,  44, 36,  63,  55, 47, 39,
								31, 23,  15,  7,  62,  54, 46, 38,
								30, 22,	 14,  6,  61,  53, 45, 37,
								29,	21,  13,  5,  28,  20, 12,  4};

// Keys rotation number of bits
int key_rotation_bits[] = {-1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Keys compression indices
int key_compression[] = {14,  17, 11, 24,  1,  5,
						  3,  28, 15,  6, 21, 10,
						  23, 19, 12,  4, 26,  8,
						  16,  7, 27, 20, 13,  2,
						  41, 52, 31, 37, 47, 55,
						  30, 40, 51, 45, 33, 48,
						  44, 49, 39, 56, 34, 53,
						  46, 42, 50, 36, 29, 32};

// Right half expansion indices
int right_text_expansion[] = {32,  1,  2,  3,  4,  5,
							   4,  5,  6,  7,  8,  9,
							   8,  9, 10, 11, 12, 13,
							  12, 13, 14, 15, 16, 17,
							  16, 17, 18, 19, 20, 21,
							  20, 21, 22, 23, 24, 25,
							  24, 25, 26, 27, 28, 29,
							  28, 29, 30, 31, 32,  1};

// Sbox 1 values
int sbox_1[] = {14,   4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
			 	 0,  15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
			 	 4,   1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
				 15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13};

// Sbox 2 values
int sbox_2[] = {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
			 	 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
			 	 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
				13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9};

// Sbox 3 values
int sbox_3[] = {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
				13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
				13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
			 	 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12};

// Sbox 4 values
int sbox_4[] = { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
				13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
				10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
			 	 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14};

// Sbox 5 values
int sbox_5[] = { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
				14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
			 	 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
				11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3};

// Sbox 6 values
int sbox_6[] = {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
				10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
			 	 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
			 	 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13};

// Sbox 7 values
int sbox_7[] = { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
				13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
			 	 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
			 	 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12};

// Sbox 8 values
int sbox_8[] = {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
			 	 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
			 	 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
			 	 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11};

// Right half final permutation before going to the next iteration
int right_text_final_permutation[] = {16,  7, 20, 21,
									  29, 12, 28, 17,
									   1, 15, 23, 26,
									   5, 18, 31, 10,
									   2,  8, 24, 14,
									  32, 27,  3,  9,
									  19, 13, 30,  6,
									  22, 11,  4, 25};


/*
This function permutes the input according to the indices given in permutation and
the input_size_bits value that shows the size of input in bits. The output is given in output arary.
*/
void permute(unsigned char* input, unsigned char* output, int* permutation, int input_size_bits)
{
	int i;
	int new_index;
	unsigned char new_byte;

	for (i=0; i<input_size_bits; i++) {
		new_index = permutation[i];
		new_byte = 0x80 >> ((new_index - 1)%8);
		new_byte &= input[(new_index - 1)/8];
		new_byte <<= ((new_index - 1)%8);

		output[i/8] |= (new_byte >> i%8);
	}
}


/*
In this function we create the iteration keys using the main key created in the main.c
*/
void make_iteration_keys(unsigned char* main_key, iteration_key* iteration_keys) {
	int i, j;
	int new_index;
	unsigned char new_byte;
	unsigned char shift_bits_1, shift_bits_2, shift_bits_3, shift_bits_4;

	// Puting the initial value of keys to zero
	for (i=0; i<8; i++) {
		iteration_keys[0].key[i] = 0;
	}

	// Doing the initial permutation on the main key using initial_key_permutaion
	permute(main_key, iteration_keys[0].key, initial_key_permutaion, main_key_size_bits);

	// Puting the initial value of other parts of the key structure for using in the rotation part
	for (i=0; i<3; i++) {
		iteration_keys[0].temp1[i] = iteration_keys[0].key[i];
	}

	iteration_keys[0].temp1[3] = iteration_keys[0].key[3] & 0xF0;

	for (i=0; i<3; i++) {
		iteration_keys[0].temp2[i] = (iteration_keys[0].key[i+3] & 0x0F) << 4;
		iteration_keys[0].temp2[i] |= (iteration_keys[0].key[i+4] & 0xF0) >> 4;
	}

	iteration_keys[0].temp2[3] = (iteration_keys[0].key[6] & 0x0F) << 4;


	/*
	In this for loop we do the main rotation operation using the main key and key_rotation_bits array.
	For this purpose we use the temp1, temp2 for storing the temporary values. 
	*/
	for (i=1; i<iterations_num+1; i++) {
		for (j=0; j<4; j++) {
			iteration_keys[i].temp1[j] = iteration_keys[i-1].temp1[j];
			iteration_keys[i].temp2[j] = iteration_keys[i-1].temp2[j];
		}

		new_index = key_rotation_bits[i];
		if (new_index == 1){
			new_byte = 0x80;
		} else {
			new_byte = 0xC0;
		}

		shift_bits_1 = new_byte & iteration_keys[i].temp1[0];
		shift_bits_2 = new_byte & iteration_keys[i].temp1[1];
		shift_bits_3 = new_byte & iteration_keys[i].temp1[2];
		shift_bits_4 = new_byte & iteration_keys[i].temp1[3];

		iteration_keys[i].temp1[0] <<= new_index;
		iteration_keys[i].temp1[0] |= (shift_bits_2 >> (8 - new_index));

		iteration_keys[i].temp1[1] <<= new_index;
		iteration_keys[i].temp1[1] |= (shift_bits_3 >> (8 - new_index));

		iteration_keys[i].temp1[2] <<= new_index;
		iteration_keys[i].temp1[2] |= (shift_bits_4 >> (8 - new_index));

		iteration_keys[i].temp1[3] <<= new_index;
		iteration_keys[i].temp1[3] |= (shift_bits_1 >> (4 - new_index));



		shift_bits_1 = new_byte & iteration_keys[i].temp2[0];
		shift_bits_2 = new_byte & iteration_keys[i].temp2[1];
		shift_bits_3 = new_byte & iteration_keys[i].temp2[2];
		shift_bits_4 = new_byte & iteration_keys[i].temp2[3];

		iteration_keys[i].temp2[0] <<= new_index;
		iteration_keys[i].temp2[0] |= (shift_bits_2 >> (8 - new_index));

		iteration_keys[i].temp2[1] <<= new_index;
		iteration_keys[i].temp2[1] |= (shift_bits_3 >> (8 - new_index));

		iteration_keys[i].temp2[2] <<= new_index;
		iteration_keys[i].temp2[2] |= (shift_bits_4 >> (8 - new_index));

		iteration_keys[i].temp2[3] <<= new_index;
		iteration_keys[i].temp2[3] |= (shift_bits_1 >> (4 - new_index));

		// Doing the final compression on the keys
		for (j=0; j<compressed_key_size_bits; j++) {
			new_index = key_compression[j];
			if (new_index <= 28) {
				new_byte = 0x80 >> ((new_index - 1)%8);
				new_byte &= iteration_keys[i].temp1[(new_index - 1)/8];
				new_byte <<= ((new_index - 1)%8);
			} else {
				new_byte = 0x80 >> ((new_index - 29)%8);
				new_byte &= iteration_keys[i].temp2[(new_index - 29)/8];
				new_byte <<= ((new_index - 29)%8);
			}

			iteration_keys[i].key[j/8] |= (new_byte >> j%8);
		}
	}
}

/*
This function does the main encryption and decryption and gets the input_text and iteration_keys and mode of
Operation (Encryption or Decryption) as the input and gives the output_text as the output
*/
void enc_dec_input_text(unsigned char* input_text, iteration_key* iteration_keys, int mode, unsigned char* output_text) {
	// Defining needed variables
	int i;
	int iteration;
	int new_index;
	unsigned char new_byte;
	unsigned char text_after_init_permutation[8];
	unsigned char left[4], right[4];
	unsigned char left_middle[4], right_middle[4], right_expanded[6], right_expanded_sbox[4];
	int key_index;
	unsigned char sbox_row, sbox_column;
	unsigned char sbox_indices;
	unsigned char text_before_final_permutation[8];

	// Puting the initial values of variables to zero
	for (i=0; i<8; i++)
		text_after_init_permutation[i] = 0;
	for (i=0; i<8; i++)
		output_text[i] = 0;

	// Doing the initial permution using initial_text_permutation on the input_text
	permute(input_text, text_after_init_permutation, initial_text_permutation, text_size_bits);

	// Separating the data to left and right to use in our functions
	for (i=0; i<4; i++)
		left[i] = text_after_init_permutation[i];
	for (i=4; i<8; i++)
		right[i-4] = text_after_init_permutation[i];

	// In this loop we do the main works of each ieration
	for (iteration=1; iteration<=iterations_num; iteration++) {
		// Putting left_middle to right and right_expanded to zero
		for (i=0; i<4; i++)
			left_middle[i] = right[i];
		for (i=0; i<6; i++)
			right_expanded[i] = 0;

		// Doing the expansion on the right value using permute function and right_text_expansion
		permute(right, right_expanded, right_text_expansion, expansion_size_bits);

		// Specifying the key_index according to the mode of operation. if the mode of
		// operation is decryption we should start the key_index from the end to start.
		if (mode == MODE_DECRYPTION) {
			key_index = iterations_num+1-iteration;
		} else {
			key_index = iteration;
		}

		// Doign the Xor between expanded right and iteration_keys
		for (i=0; i<6; i++) {
			right_expanded[i] ^= iteration_keys[key_index].key[i];
		}

		// putting the initial value of right_expanded_sbox to zero
		for (i=0; i<4; i++) {
			right_expanded_sbox[i] = 0;
		}


		// In this part We lookup the values from the Sboxes and fill the right_expanded_sbox
		// Generating Byte 1 of right_expanded_sbox
		sbox_indices = (right_expanded[0] >> 2) & 0x3F;
		sbox_row = 0 | (sbox_indices & 0x01) | ((sbox_indices & 0x20) >> 4);
		sbox_column = 0 | ((sbox_indices & 0x1E) >> 1);
		right_expanded_sbox[0] |= ((unsigned char)sbox_1[sbox_row*16+sbox_column] << 4);

		sbox_indices = ((right_expanded[0] & 0x03) << 4) | ((right_expanded[1] & 0xF0) >> 4) & 0x3F;
		sbox_row = 0 | (sbox_indices & 0x01) | ((sbox_indices & 0x20) >> 4);
		sbox_column = 0 | ((sbox_indices & 0x1E) >> 1);
		right_expanded_sbox[0] |= (unsigned char)sbox_2[sbox_row*16+sbox_column];

		// Generating Byte 2 of right_expanded_sbox
		sbox_indices = ((right_expanded[1] & 0x0F) << 2) | ((right_expanded[2] & 0xC0) >> 6) & 0x3F;
		sbox_row = 0 | (sbox_indices & 0x01) | ((sbox_indices & 0x20) >> 4);
		sbox_column = 0 | ((sbox_indices & 0x1E) >> 1);
		right_expanded_sbox[1] |= ((unsigned char)sbox_3[sbox_row*16+sbox_column] << 4);


		sbox_indices = (right_expanded[2]) & 0x3F;
		sbox_row = 0 | (sbox_indices & 0x01) | ((sbox_indices & 0x20) >> 4);
		sbox_column = 0 | ((sbox_indices & 0x1E) >> 1);
		right_expanded_sbox[1] |= (unsigned char)sbox_4[sbox_row*16+sbox_column];

		// Generating Byte 3 of right_expanded_sbox
		sbox_indices = (right_expanded[3] >> 2) & 0x3F;
		sbox_row = 0 | (sbox_indices & 0x01) | ((sbox_indices & 0x20) >> 4);
		sbox_column = 0 | ((sbox_indices & 0x1E) >> 1);
		right_expanded_sbox[2] |= ((unsigned char)sbox_5[sbox_row*16+sbox_column] << 4);


		sbox_indices = ((right_expanded[3] & 0x03) << 4) | ((right_expanded[4] & 0xF0) >> 4) & 0x3F;
		sbox_row = 0 | (sbox_indices & 0x01) | ((sbox_indices & 0x20) >> 4);
		sbox_column = 0 | ((sbox_indices & 0x1E) >> 1);
		right_expanded_sbox[2] |= (unsigned char)sbox_6[sbox_row*16+sbox_column];

		// Generating Byte 4 of right_expanded_sbox
		sbox_indices = ((right_expanded[4] & 0x0F) << 2) | ((right_expanded[5] & 0xC0) >> 6) & 0x3F;
		sbox_row = 0 | (sbox_indices & 0x01) | ((sbox_indices & 0x20) >> 4);
		sbox_column = 0 | ((sbox_indices & 0x1E) >> 1);
		right_expanded_sbox[3] |= ((unsigned char)sbox_7[sbox_row*16+sbox_column] << 4);


		sbox_indices = (right_expanded[5]) & 0x3F;
		sbox_row = 0 | (sbox_indices & 0x01) | ((sbox_indices & 0x20) >> 4);
		sbox_column = 0 | ((sbox_indices & 0x1E) >> 1);
		right_expanded_sbox[3] |= (unsigned char)sbox_8[sbox_row*16+sbox_column];

		// Putting the initial value of right_middle to zero
		for (i=0; i<4; i++) {
			right_middle[i] = 0;
		}

		// Doing the final permutation on the right value
		permute(right_expanded_sbox, right_middle, right_text_final_permutation, text_size_bits/2);

		// Doing the final Xor and creating left and right for the next iteration
		for (i=0; i<4; i++)
			right_middle[i] ^= left[i];
		for (i=0; i<4; i++) {
			left[i] = left_middle[i];
			right[i] = right_middle[i];
		}
	}

	// Filling text_before_final_permutation
	for (i=0; i<4; i++)
		text_before_final_permutation[i] = right[i];

	for (i=4; i<8; i++) 
		text_before_final_permutation[i] = left[i-4];

	// Final permutation of input to generate the output using final_text_permutation
	permute(text_before_final_permutation, output_text, final_text_permutation, text_size_bits);
}
