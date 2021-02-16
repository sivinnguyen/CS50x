// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Size of dictionary
unsigned int words = 0;

// Is dictionary loaded?
bool loaded = false;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    bool isExist = false;

    // Get hash number
    unsigned int index = hash(word);
    node *cursor = table[index];

    /*
    if(table[index] != NULL)
    {
        int cmp;
        // Search
        node *cursor = table[index];
        do {
            // Returning true if found
            cmp = strcasecmp(cursor->word, word);
            if( cmp == 0)
            {
                isExist = true;
                break;
            }
            // else continue searching
            cursor = cursor->next;

        }
        while(cursor->next != NULL); // BUG HERE
    }
    */

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            isExist = true;
            break;
        }
        // else continue searching
        cursor = cursor->next;
    }

    return isExist;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char *alphabet = "abcdefghijklmnopqrstuvwxyz";
    // Pointer of first character of word
    char *c;
    unsigned int index;

    // Finds the first occurrence of a character in the alphabet string, return pointer
    c = strchr(alphabet, tolower(word[0]));
    // Subtract the alphabet address from what strchr returns to get index
    // https://stackoverflow.com/a/3217634/1813901
    index = (unsigned int)(c - alphabet);

    return index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        return false;
    }

    // Read words from dictionary file
    char word[LENGTH + 1]; // +1 for '\0'
    while (fscanf(inptr, "%s", word) == 1)
    {
        // Get hash number
        unsigned int index = hash(word);

        // Create word node
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);

        // Insert to hash table
        if (table[index] == NULL)
        {
            n->next = NULL;
        }
        else
        {
            n->next = table[index];
        }

        table[index] = n;

        // Calculate size of dictionary
        words++;
    }

    // Check whether there was an error when working with file
    if (ferror(inptr))
    {
        fclose(inptr);
        return false;
    }

    // Close dictionary file
    fclose(inptr);

    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (!loaded)
    {
        return 0;
    }

    return words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int i;
    for (i = 0; i < N; ++i)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    loaded = false;
    return true;
}
