/* By: Venu
*  Date: 30/03/16
*  Copyright 2016
*  Description: Given a string, we need to print all possible palindromes that
*  can be generated *  using letters of that string.
*  Examples: Input: str = “aabcb” Output: abcba bacab
*  Input: str = “aabbcadad” Output: aabdcdbaa aadbcbdaa abadcdaba abdacadba
*  adabcbada adbacabda baadcdaab badacadab bdaacaadb daabcbaad dabacabad dbaacaabd
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FALSE 1 
#define TRUE 0
#define LETTERS_IN_ALPHABET 26

typedef unsigned int uint;

/* Swap two characters at given addresses */
void swap(char *x, char *y) {
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* Reverse a given string inplace */
char * str_reverse(char *str) {
    uint i = 0;
    uint len = strlen(str);
    for (i = 0; i < (len/2); i++)
        swap((str+i), (str+(len-i-1)));
    return str;
}

/* Given a string print all possible unique combinations of palindromes.
   str + centre_char (if available) + reversed str = palindrome

    str = input string with each character's frequency reduced by half
    that of the original string
    s = start index of character in string
    e = end index of character in string i.e. string length
    centre_char = in case of odd string length, this will be the
    char that occurs odd number of times i.e the char to be placed
    in the centre of the palindrome. In case of even string length
    this will be NULL

    RETURNS total number of palindrome permutations
*/
uint str_permutations(char *str, uint s, uint e, char *centre_char) {
    uint i = 0;
    static uint perm_cnt = 0;
    char *str_rev = NULL;
    if (s == e) {
        perm_cnt++;
        if (!str) {
            /* str can be null if the string is just one char long */
            printf("%c\n", *centre_char);
            goto END;
        }
        /* string to print the reverse of the permuted string */
        str_rev = (char *)malloc((strlen(str) + 1) * sizeof(char));
        strcpy(str_rev, str);
        if (centre_char)
            printf("%s%c%s\n", str, *centre_char, str_reverse(str_rev));
        else
            printf("%s%s\n", str, str_reverse(str_rev));
        free(str_rev);
    } else {
        for (i = s; i <= e; i++) {
            /* No need to swap and permute same characters. Avoids repetition */
            if ((s != i) && (*(str+s) == *(str+i)))
                continue;
            swap((str+s), (str+i));
            str_permutations(str, s+1, e, centre_char);
            swap((str+s), (str+i));
        }
    }
END:
    return perm_cnt;
}

/* Processes the input string and outputs a string with characters at half the
   frequency
    str = input string
    len = input string length
    unq_chars = output string of chars at half frequency
    central_char = output centre character if strlen is odd else NULL
    
    RETURNS TRUE if input string is valid to generate palindromes else
    returns FALSE */
int get_halfStr_Ctrchar(char *str, uint len,
        char * unq_chars, char *central_char) {
    uint i = 0, j = 0, repeat = 0, num_central_unq = 0;
    uint alphabet[LETTERS_IN_ALPHABET];
    char in_ch;

    for (i = 0; i < LETTERS_IN_ALPHABET; i++)
        alphabet[i] = 0;

    for (i = 0; i < len; i++) {
        in_ch = *(str+i);
        if (in_ch < 'a' || in_ch > 'z') {
            printf("ERROR: Only enter chars between a to z\n");
            return FALSE;
        }
        /* Histogram of characters in the input string */
        alphabet[in_ch - 'a']++;
        /*printf("i:%u len:%u in_ch = %c diff:%u alphabet=%u\n", i, len, in_ch,
                in_ch - 'a', alphabet[in_ch - 'a']);*/
    }

    for (i = 0; i < LETTERS_IN_ALPHABET; i++) {
        if (alphabet[i] & 0x1) {
            /* if the number of occurences of a character is odd, it
            is the centre character */
            num_central_unq++;
            *central_char = ('a'+ i);
            //printf("centre char=%c num_ctr:%u\n", *central_char, num_central_unq);
        }
        /* Half the frequency of characters */
        repeat = alphabet[i]/2;
        for (j = 0; j < repeat; j++) 
            *unq_chars++ = 'a' + i;
    }
    *unq_chars = '\0';

    /* There can be none or just one centre character */
    if (num_central_unq > 1) {
        printf("ERROR: The given input string cannot be categorized into "
               "palindromes!\n");
        return FALSE;
    }
    /* if strlen is even then there is no unique centre character */
    if (len % 2 == 0)
        central_char =  NULL;

    return TRUE;
}

int main(int argc, char *argv[]) {
    int rc = TRUE, n = 0;
    char inp_str[256], unq_chars[128], central_char;
    uint inp_str_len = 0, num_perm = 0;
    printf("Enter String: ");
    n = scanf("%s", inp_str);
    inp_str_len = (uint)strlen(inp_str);
    printf("Entered %d string(s) of length %u\n", n, inp_str_len);
    rc = get_halfStr_Ctrchar(inp_str, inp_str_len, unq_chars, &central_char);
    if (!rc) {
        printf("Unique char string = %s, cental_char = %c\n", unq_chars,
            central_char);
        inp_str_len = strlen(unq_chars);
        /* In case of input string of just 1 char, there will only be
         a centre char and unique chars will be NULL */
        inp_str_len = (inp_str_len > 0) ? inp_str_len : 1;
        num_perm = str_permutations(unq_chars, 0, (inp_str_len-1),
                &central_char);
        printf("Total number of Palindromes = %u\n", num_perm);
    }
    return rc;
}
