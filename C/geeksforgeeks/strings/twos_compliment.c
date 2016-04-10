/* By: Venu
*  Date: 09/04/16
*  Copyright 2016
*  Description: For a given string of binary number find the two’s complement
*  of it.
*/

#include <stdio.h>
#include <string.h>

#define FALSE 1 
#define TRUE 0

typedef unsigned int uint;

/* 2's complement of a string */
void twos_complement(char * str, char * out) {
	int i = 0;
	uint len = strlen(str);
	
	/* 1's Complement */
	for (i = 0; i < len; i++) {
		if (*(str+i) == '0')
			*(str+i) = '1';
		else if (*(str+i) == '1')
			*(str+i) = '0';
		else
			printf("ERROR: Invalid input %c\n", *(str+i));			
	}
	
	/* 2's complement - flips 1s to 0s until first 0 is encountered */
	for (i = (len - 1); i >= 0; i--) {
		if (*(str+i) == '0') {
			*(str+i) = '1';
			break;
		} else {
			*(str+i) = '0';
		}
	}
	
	/* In case of all 1s after 1s complement then append 1 to the beginning */
	if (i == -1)
		*out++ = '1';
	strcpy(out, str);
}

int main(int argc, char *argv[]) {
	int rc = TRUE;
	char in_str[256], out_str[256];
	scanf("%s", in_str);
	twos_complement(in_str, out_str);
	printf("%s\n", out_str);
	return rc;
}



