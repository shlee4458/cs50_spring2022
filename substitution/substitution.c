#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int find_index(char plaintext_e);
int duplicate(string cipher);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error 1: input one command line argument.\n");
        return 1;
    }

    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    else
    {
        // if CLA not 26 return 1
        // turn all the cipher into lowercase string and save it into a string
        int n = strlen(argv[1]);
        char cipher[n];
        for (int i = 0; i < n + 1; i++)
        {
            cipher[i] = tolower(argv[1][i]);
        }

        for (int i = 0; i < n; i++)
        {
            if (isalpha(argv[1][i]) == 0)
            {
                printf("Provide alphabets only");
                return 1;
            }
        }

        if (duplicate(cipher) == 1)
        {
            printf("Provide valid key.\n");
            return 1;
        }

        else
        {
            // prompt for an input
            string plaintext = get_string("plaintext:  ");

            // loop through the plaintext
            int m = strlen(plaintext);
            char ciphertext[m];
            for (int i = 0; i < m + 1; i++)
            {
                if (i < m)
                {
                    // find the index of plaintext
                    // take that index to find the element in the cipher
                    // take that cipher and plug into the ciphertext
                    int idx = find_index(plaintext[i]);
                    if (idx == 100)
                    {
                        ciphertext[i] = plaintext[i];
                    }
                    else
                    {
                        if (isupper(plaintext[i]))
                        {
                            ciphertext[i] = toupper(cipher[idx]);
                        }
                        else
                        {
                            ciphertext[i] = cipher[idx];
                        }
                    }
                }
                else
                {
                    ciphertext[i] = '\0';
                }
            }
            printf("ciphertext: %s", ciphertext);
            printf("\n");
            return 0;
        }
    }
}

int find_index(char plaintext_e)
{
    // 65~90 upper, 97~122 lower
    int idx;

    if (isupper(plaintext_e))
    {
        idx = plaintext_e - 65;
    }
    else if (islower(plaintext_e))
    {
        idx = plaintext_e - 97;
    }
    else
    {
        idx = 100;
    }
    return idx;
}

int duplicate(string cipher)
{
    int count = 0;
    int n = strlen(cipher);
    int i;
    int j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < strlen(cipher); j++)
        {
            if (cipher[i] == cipher[j])
            {
                count++;
            }
        }
    }

    if (count > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
