#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

char rotate(char text_element, int key);

int main(int argc, string argv[])
{
    // take one command line argument as a input for key value
    // if command line input more than 1 or 0, return 1
    if (argc != 2)
    {
        printf("Error 1: Input a key for the command line argument\n");
        return 1;
    }
    // If CLA input is not a number, return 1
    else
    {
        int n = strlen(argv[1]);
        for (int i = 0; i < n; i++)
        {
            if (argv[1][i] < 48 || 57 < argv[1][i])
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        // save the CLA as key
        int key = atoi(argv[1]);

        // prompt for input "plaintext:
        string text = get_string("plaintext:  ");

        printf("ciphertext: ");

        int m = strlen(text);
        char cyphertext[n];

        for (int i = 0; i < m; i++)
        {
            char ciphertext = rotate(text[i], key);
            printf("%c", ciphertext);
        }
        printf("\n");

        return 0;
    }
}


// input should be rotated by 26
// only alphabets, caps should not be changed
// output cyphertext:
char rotate(char text_element, int key)
{
    char ciphertext_before;
    char ciphertext;
    char indexe;

    if (isupper(text_element))
    {
        indexe = text_element - 65;
        ciphertext_before = (indexe + key) % 26;
        ciphertext = ciphertext_before + 65;
    }
    else if (islower(text_element))
    {
        indexe = text_element - 97;
        ciphertext_before = (indexe + key) % 26;
        ciphertext = ciphertext_before + 97;
    }
    else
    {
        ciphertext = text_element;
    }
    return ciphertext;
}