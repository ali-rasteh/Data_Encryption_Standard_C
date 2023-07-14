#include "utils.h"
#include "includes.h"

/*
This function get a char value and prints its binary value with 0, 1
*/
void print_binary_value(char character) {
	int i;
	for (i=0; i<8; i++) {
		if ((character>>(7-i))&0x01) {
			printf("1");
		} else {
			printf("0");
		}
	}
}