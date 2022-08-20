// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count[1] = {0};
FILE *dict = NULL;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int ch = hash(word);
    node *cursor = table[ch];
    while (cursor != NULL)
    {
       int result = strcasecmp(word, cursor->word);
       if (result == 0)
       {
        return true;
       }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int j = toupper(word[0]);
    j-= 65;

    // TODO: Improve this hash function
    return j;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    dict = fopen(dictionary, "r");
    char wrd[LENGTH + 1];
    bool first = true;
    int l = -1;
   if (dict == NULL)
    // TODO
    {
        printf("error loading dictionary");
    return false;
    }

       while (fscanf(dict, "%s", wrd) != EOF)
       {

       int j = hash(wrd);
       if (l != j)
       {
        first = true;
       }
       l = j;
       if (first == true)
       {
       node *n = malloc(sizeof(node));
       strcpy(n->word, wrd);
       n->next = NULL;
       table[j] = n;
       count[0] += 1;
       first = false;
       }
       else
       {
       node *n = malloc(sizeof(node));
       strcpy(n->word, wrd);
       n->next = table[j];
       table[j] = n;
       count[0] += 1;
       }
       }
       return true;
    }





// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (count[0] > 0)
    {
        return count[0];
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
    while (table[i] != NULL)
    {
        node *tmp = table[i]->next;
        free(table[i]);
        table[i] = tmp;
    }
    }
   if (fclose(dict) == 0)
   {
    return true;
   }

    return false;
}
