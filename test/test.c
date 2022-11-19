#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string sentence = "Hello, how are you";
    int letter = strlen(sentence);
    printf("%i\n", letter);
}