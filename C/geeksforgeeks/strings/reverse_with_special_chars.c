/* By: Venu
*  Date: 05/02/16
*  Copyright 2016
*  Description: Given a string, that contains special character together
*  with alphabets (‘a’ to ‘z’ and ‘A’ to ‘Z’), reverse the string in a way
*  that special characters are not affected
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FALSE 0 
#define TRUE 1

/* Swap two characters at given addresses */
void swap(char *x, char *y) {
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* Check if a character is a letter or not */
int isLetter(char x) {
    int rc = FALSE;
    if (((x - 'a') >= 0 && (x - 'z') <= 0) ||
        ((x - 'A') >= 0 && (x - 'Z') <= 0)) {
        rc = TRUE;
    }
    return rc;
}

void reverse_special(char *str, int len) {
    int start = 0, end = len - 1;
    while (start <= end) {
        if (!isLetter(str[start]))
            start++;
        else if (!isLetter(str[end]))
            end--;
        else {
            swap(&str[start], &str[end]);
            start++;
            end--;
        }
    }
    printf("Reversed String = %s\n", str);
}

int main(int argc, char *argv[]) {
    char str[256];
    int n = 0, len = 0;
    printf("Enter String: ");
    n = scanf("%s", str);
    len = strlen(str);
    printf("Entered %d string of size %d\n", n, len);
    reverse_special(str, len);
    return EXIT_SUCCESS;
}

