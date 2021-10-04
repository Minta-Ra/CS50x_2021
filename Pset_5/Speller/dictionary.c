// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"




// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 500;

// Hash table
node *table[N];

////////////////////////////////////////////////////////////////////////////////

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int wordLength = strlen(word);
    char lowerWord[LENGTH + 1];

    for (int i = 0; i < wordLength; i++)
    {
        if (isupper(word[i]))
        {
            lowerWord[i] = tolower(word[i]);
        }
        else
        {
            lowerWord[i] = word[i];
        }
    }

    // ADD \0 TO THE END OF ARRAY
    lowerWord[wordLength] = '\0';

    // HASH WORD TO OBTAIN A HASH VALUE
    int hashValue = hash(lowerWord);
    node *cursor = table[hashValue];
    // ACCESS LINKED LIST AT THE INDEX IN THE HASH TABLE
    while (table[hashValue] != NULL)
    {
        // TRAVERSE LINKED LIST, LOOKING FOR WORD - CHECK IF THE WORD IS THE SAME AS IN THE HASH (WORD IN A DICTIONARY)
        if (strcmp(cursor->word, lowerWord) == 0)
        {
            return true;
        }
        // MOVE TO THE NEXT NODE
        cursor = cursor->next;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////

// Hashes word to a number // Hash function
// OUTPUT BETWEEN 0 AND N-1
unsigned int hash(const char *word)
{
    // TODO
    unsigned int hash = 5381;
    int i;

    while ((i = *word++) != '\0')
    {
        hash = ((hash << 5) + hash) + i;    /* hash * 33 + i */
    }

    hash = hash % N;
    return hash;
}

////////////////////////////////////////////////////////////////////////////////

// WORD TOTAL FROM LOADED FILE FOR RETURN IN SIZE FUNCTION
int wordTotal = 0;

// Loads dictionary into memory, returning true if successful, else false
// LOAD FROM DICTIONARY TO HASH TABLE (ARRAY OF LINKED LISTS)
bool load(const char *dictionary)
{
    // TODO
    // OPEN DICTIONARY FILE
    FILE *dfile = fopen(dictionary, "r");
    if (dfile == NULL)
    {
        fclose(dfile);
        return false;
    }

    char dword[LENGTH + 1];


    // READ STRINGS FROM FILE ONE AT A TIME
    while (fscanf(dfile, "%s", dword) != EOF)
    {
        // CREATE A NEW NODE FOR EACH WORD
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(dfile);
            return false;
        }
        // OTHERWISE
        strcpy(n->word, dword);


        // HASH WORD TO OBTAIN A HASH VALUE
        // HASH FUNCTION (TAKES INPUT A STRING, OUTPUT IS A NUMBER)
        unsigned int hashValue = hash(n->word);
        wordTotal++;


        // INSERT NODE INTO HASH TABLE AT THAT LOCATION
        if (table[hashValue] == NULL)
        {
            table[hashValue] = n;
            n->next = NULL;
        }
        else
        {
            n->next = table[hashValue];
            table[hashValue] = n;
        }
    }
    fclose(dfile);
    return true;
}

////////////////////////////////////////////////////////////////////////////////

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordTotal;
}

////////////////////////////////////////////////////////////////////////////////

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *temp = cursor;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}