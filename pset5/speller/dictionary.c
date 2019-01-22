// Implements a dictionary's functionality

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "dictionary.h"
#include <string.h>
#include <strings.h>

//Define HASHSIZE here to make it simpler to change for speed optimisation.
#define HASHSIZE 50000

// Define int for the count function
int wordcount;

// Create a structure called node, containing a var called word.
typedef struct node
{
    char word[ LENGTH + 1];
    struct node *next;
}
node;

// Create a root for the hash table, one bucket for each letter.
node *hashtable[HASHSIZE] = {NULL};

// Hash function from http://www.cse.yorku.ca/~oz/hash.html < I changed the initial long.
unsigned int hash(char *dictword)
{
    int hash = 27;
    int c = 0;

    while (c == *dictword++)
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASHSIZE;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{

    char change[ strlen(word) + 1];
    strcpy(change, word);

    // Set cursor to the correct bucket in the hashtable, using the hashed holder string
    int head = hash(change);
    node *cursor = hashtable[head];

    // Compare the word against the values in the linked list.
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor -> next;
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // For each word in the dictionary text file, store it in the dict data struct. Linked list.
    // When creating a node, you just want to malloc a node pointer. (allocate a node some memory)
    //Load in the dictionary & check it loaded.
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        fprintf(stderr, "Could not open the supplied dicitonary\n");
        return false;
    }

    char dict_word[ LENGTH + 1];

    // Through the whole dictionary file, look for strings, and put them in var word, until EOF.
    while (fscanf(dict, "%s", dict_word) != EOF)
    {

        // Get the hash bucket the word will go in
        int hashValue = hash(dict_word);

        wordcount++ ;
        //Malloc a node for each word found.
        node *new_node = malloc(sizeof(node));

        // Insert word from the dictionary to the new node. M
        strcpy(new_node->word, dict_word);

        //decide if to insert or append to a hashtable index
        if (hashtable[hashValue] == NULL)
        {
            hashtable[hashValue] = new_node;
            new_node -> next = NULL;
        }
        else
        {
            new_node->next = hashtable[hashValue];
            // Insert a pointer to null for the next node.
            hashtable[hashValue] = new_node;
        }
    }

    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (wordcount > 0)
    {
        return wordcount;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    // Iterate through each value in the array (pointer to linked list, index)
    for (int i = 0; i < HASHSIZE; i++)
    {
        // Set cursor to the node located at that index
        node *cursor = hashtable[i];

        // Until the cursor doesn't point to a next value, free the memory, using a temporary node.
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;

}
