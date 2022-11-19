#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int isletter(int letter);
int ispunctuation(int letter);
float count_num_letters(string text);
float count_num_words(string text);
float count_num_sentences(string text);
float cal_cli_index(float num_letters, float num_words, float num_sentences);

int main(void)
{
    //ask for prompt for a text
    string text = get_string("Input Text Here: ");

    //count the number of letters in the text
    float num_letters = count_num_letters(text);

    //count the number of words in the text
    float num_words = count_num_words(text);

    //count the number of sentences in the text
    float num_sentences = count_num_sentences(text);

    //calculate CLI index
    //0.0588 * L - 0.296 * S - 15.8
    //L = number of letters per words, S = number of words per sentence
    //round the number
    float cli_index = cal_cli_index(num_letters, num_words, num_sentences);

    //print out the Grade
    //less than 1 -> before grade 1
    //equal or larger than 16 -> Grade 16+
    if (cli_index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (cli_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(cli_index));
    }
}

//loop through elements and add 1 for every loop
// if 65~90, 97~122 add a counter

int isletter(int letter)
{
    if (letter >= 65 && letter <= 90)
    {
        return 1;
    }
    else if (letter >= 97 && letter <= 122)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int ispunctuation(int letter)
{
    if (letter == 33 || letter == 46 || letter == 63)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

float count_num_letters(string text)
{
    float num_letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isletter(text[i]) == 1)
        {
            num_letters++;
        }
    }
    return num_letters;
}

float count_num_words(string text)
{
    float num_spaces = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 32)
        {
            num_spaces++;
        }
    }
    return num_spaces + 1;
}
float count_num_sentences(string text)
{
    float num_sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (ispunctuation(text[i]) == 1)
        {
            num_sentences++;
        }
    }
    return num_sentences;
}

//0.0588 * L - 0.296 * S - 15.8
//L = number of letters per words, S = number of words per sentence

float cal_cli_index(float num_letters, float num_words, float num_sentences)
{
    float L = 0;
    float S = 0;
    L = num_letters / num_words * 100.0;
    S = num_sentences / num_words * 100.0;
    float cli = 0.0588 * L - 0.296 * S - 15.8;
    return cli;
}