#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string

    //make a list of lowercase alphabets (ASCII 97~122 : a~z)
    int alphabets[26];
    int sum = 0;

    for (int i = 0; i < 26; i++)
    {
        alphabets[i] = 'a' + i;
    }

    //transform uppercase to lowercase
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (word[i] >= 65 && word[i] <= 90)
        {
            word[i] = word[i] + 32;
        }
    }

    //parse through input and see what index matches each character of the array
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (alphabets[j] == word[i])
            {
                sum = sum + POINTS[j];
            }
        }
    }
    return sum;
}
