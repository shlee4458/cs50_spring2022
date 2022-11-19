// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 44;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // create a pointer to the index returned from the hash function in the hash table
    for (node *newNode = table[hash(word)]; newNode != NULL; newNode = newNode->next)
    {
        if (strcmp(newNode->word, word)) // compare the string of the node and the word
        {
            return true;
        }
    }

    // if not in the dictionary return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (strlen(word) == 1 || strlen(word) == 2 || strlen(word) == 3 || strlen(word) >= 14)
    {
        return 43;
    }
    else
    {
        return (toupper(*word) - 'A') % 43;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char c;
    char vocab[LENGTH + 1];
    int index = 0;
    node *newNode;
    // open the file
    FILE *file = fopen(dictionary, "r");

    // read the file char by char and find a word
    while (fread(&c, sizeof(char), 1, file))
    {
        if (isalpha(c) || (c == '\'' && index > 0)) // keep append to the word until forms a word
        {
            vocab[index] = c;
            index++;
        }
        else
        {
            // hash the word and append in the table
            for (node *n = table[hash(vocab)]; n->next == NULL; n = n->next)
            {
                if (n == NULL)
                {
                    vocab[index] = '\0';
                    n->word = vocab; // add vocab to word
                }
            }
            index = 0;
        }
    }

    // close the file
    fclose(file);

    // write the file

    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
