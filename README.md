# Data Encryption Standard (DES) C Implementation

## Overview
This project provides a C implementation of the Data Encryption Standard (DES) algorithm. The implementation includes functionalities for key generation, encryption, and decryption.

## File Structure
- **main.c**: Contains the main function which sets up the DES encryption/decryption process, including key and input text initialization.
- **utils.c**: Provides utility functions, such as printing binary values.
- **includes.h**: Header file including necessary libraries and other header files.
- **des.h**: Header file defining constants, structures, and function prototypes related to DES.
- **des.c**: Includes the core DES algorithm functions, such as key generation and encryption/decryption operations.

## Dependencies
The project requires the following standard libraries:
- `stdio.h`
- `stdlib.h`
- `string.h`
- `time.h`

## Functions
- **print_binary_value**: Prints the binary representation of a given character.
- **make_main_key**: Generates the main key used for DES encryption.
- **fill_input_text**: Fills the input text with predefined values for encryption.
- **make_iteration_keys**: Creates iteration keys from the main key.
- **permute**: Applies a given permutation to the input.
- **enc_dec_input_text**: Encrypts or decrypts the input text based on the mode specified.

## Compilation and Execution
To compile and run the project, use the following commands:

```sh
gcc -o des main.c des.c utils.c
./des
```

## License
This project is licensed under the MIT License.
