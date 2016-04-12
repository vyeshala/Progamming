/* By: Venu
   Date: 12/04/16
   Copyright 2016
   Description: Given a string and number of rows ‘n’. Print the string formed
   by concatenating n rows when input string is written in row-wise Zig-Zag
   fashion.
	Input: str = "GEEKSFORGEEKS"
       n = 3
	Output: GSGSEKFREKEOE
	Explanation: Let us write input string in Zig-Zag fashion
             in 3 rows.
	G       S       G       S
	  E   K   F   R   E   K
		E       O       E
	Now concatenate the two rows and ignore spaces 
	in every row. We get "GSGSEKFREKEOE"
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void process_zigzag(char *str, int n) {
	char arr[n][256];
	int i = 0, j = 0, len = 0;
	/* When #rows is 1, just print the input string */
	if (n == 1) {
		printf("%s\n", str);
		return;
	}

	for (j = 0; j < n; j++)
		arr[j][0] = '\0';

	len = strlen(str);
	
	while (i < len) {
		/* Downward traversal till n rows */
		for (j = 0; j < n; j++) {
			strncat(arr[j], (str+i), 1);
			i++;
			if (i >= len) break;
		}
		/* Upward traversal from last but one row to second from first */
		for (j = (n-2); j >= 1; j--) {
			strncat(arr[j], (str+i), 1);
			i++;
			if (i >= len) break;
		}
	}
	
	/* Concatenate all the rows into the first */
	for (i = 1; i < n; i++)
		strcat(arr[0], arr[i]);

	printf("%s\n", arr[0]);
}

int main(int argc, char *argv[]) {
	char str[256];
	int n = 0;
	scanf("%d", &n);
	scanf("%s", str);
	process_zigzag(str, n);
	return 0;
}
