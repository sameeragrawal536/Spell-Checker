// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include <cs50.h>
#include <unistd.h>
#include "dictionary.h"

// Represents a node in a hash table
char wordly[4];
char wordly2[2];
char wordyay[45];
char programmer2[45];
int ASCII[2];
int ASCII2[1];
int k;
bool spelled;
int a = 1;
int j = 0;

/* Defining the data type "node" for our linked list. A linked list of composed of nodes, which contain both a String variable and a pointer to the next element
in the linked list. */
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

/* Hashing each word according to its first two characters. This hash function will be used on every word in the dictionary in order to organize the words and make 
it more efficient to search through. This creates 676 total "buckets" into which words can be hashed. The word "cab", for example, would be hashed into to bucket 
79. The letter "C" is represented by the number 3, and  the letter "A" is represented by the number 1. The number is calculated by taking the result of 26*3+1. */
unsigned int hash(const char *word)
{
    strcpy(programmer2, word);
    ASCII[0] = 0;
    ASCII[1] = 0;
    ASCII2[0] = 0;
    if ((strlen(programmer2)) >= 2)
    {
        // Making first two characters lowercase
        for (int epicly2 = 0; epicly2 < 2; epicly2++)
        {
            if (65 <= ((int) (programmer2[epicly2])) && ((int) (programmer2[epicly2])) <= 90)
            {
                programmer2[epicly2] = programmer2[epicly2] + 32;
            }
        }
        if (97 < ((int) (programmer2[0])) || ((int) (programmer2[0])) > 122)
        {
            return 0;
        }
        if (97 < ((int) (programmer2[1])) || ((int) (programmer2[1])) > 122)
        {
            return 0;
        }
        
        // Convert ASCII values of characters from numbers between 97 & 122 to numbers between 1 & 26
        for (int epicly = 0; epicly < 2; epicly++)
        {
            if (epicly == 0)
            {
                char c = programmer2[epicly];
                ASCII[epicly] = c - 97;
            }
            else
            {
                char c2 = programmer2[epicly];
                ASCII[epicly] = c2 - 97;
            }
        }
           
        // Return the result of the calculation
        return 26*ASCII[0] + ASCII[1];
    }
    else
    {
        if (65 <= ((int) (programmer2[0])) && ((int) (programmer2[0])) <= 90)
        {
            programmer2[0] = programmer2[0] + 32;
        }
        char c3 = programmer2[0];
        ASCII2[0] = c3 - 97;
        return 26*ASCII2[0];
    }
    printf("Hashed!\n");
}
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *ptr1 = fopen("large", "r");
    if (ptr1 == NULL)
    {
        printf("The very first ptr is null.\n");
        return false;
    }
    node *list = malloc(sizeof(node));
    if (list == NULL)
    {
        printf("The very first malloc is null.\n");
        return false;
    }
    char wordyay2[45];
    list -> next = NULL;
    fscanf(ptr1, "%s", wordyay2);
    while((feof(ptr1)) == 0)
    {
        fscanf(ptr1, "%s", wordyay2);
        j++;
    }
    node *arr[j];
    rewind(ptr1);
    for (k = 0; k < j; k++)
    {
        node *b = malloc(sizeof(node));
        if (b == NULL)
        {
            printf("We failed to load the word number %i from the dictionary.\n", k);
            return false;
        }
        arr[k] = b;
        fscanf(ptr1, "%s", wordyay2);
        strcpy((arr[k] -> word), wordyay2);
        arr[k] -> next = NULL;
    }
    list -> next = arr[0];
    k = 0;
    for (k = 0; k < N; k++)
    {
        table[k] = malloc(sizeof(node));
    }
    int as = 0;
    for (k = 0; k < j; k++)
    {
        unsigned int epic = hash(arr[k] -> word);
        if ((table[epic] -> next) == NULL)
        {
            table[epic] -> next = arr[k];
        }
        else
        {
            node *tmp = table[epic];
            while (tmp -> next != NULL)
            {
                tmp = tmp -> next;
                if (tmp -> next == NULL)
                {
                    tmp -> next = arr[k];
                    printf("Yes #%i\n!", k);
                    break;
                }
            }
        }
    }
    printf("Loading + hashing complete!\n");
    return true;
}

bool check(const char *word)
{
    unsigned int programmer = hash(word);
    node *tmp2 = table[programmer];
    if (strlen(programmer2) <= 45)
    {
        while (tmp2 -> next != NULL)
        {
            for (int epicly2006 = 0; epicly2006 < strlen(programmer2); epicly2006++)
            {
                if (65 <= ((int) (programmer2[epicly2006])) && ((int) (programmer2[epicly2006])) <= 90)
                {
                    programmer2[epicly2006] = programmer2[epicly2006] + 32;
                }
                else
                {
                    programmer2[epicly2006] = programmer2[epicly2006];
                }
            }
            if (strlen(tmp2 -> word) == strlen(programmer2))
            {
                if ((strncmp((tmp2 -> word), (programmer2), (strlen(programmer2)))) == 0)
                {
                    spelled = true;
                    break;
                }
                else
                {
                    tmp2 = tmp2 -> next;
                }
            }
            else
            {
                tmp2 = tmp2 -> next;
            }
        }
        if (tmp2 -> next == NULL)
        {
            if  (strlen(tmp2 -> word) == strlen(programmer2))
            {
                if ((strncmp(tmp2 -> word, programmer2, strlen(programmer2))) == 0)
                {
                    spelled = true;
                }
                else
                {
                    //printf("The word %s is spelled wrong.\n", programmer2);
                    spelled = false;
                }
            }
            else
            {
                //printf("The word %s is spelled wrong.\n", programmer2);
                spelled = false;
            }
        }
    }
    else
    {
        spelled = false;
    }
    if (spelled == false)
    {
        return false;
    }
    else
    {
        return true;
    }
}
// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int *ip;
    ip = &j;
    return *ip;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor = table[0] -> next;
    node *tmp4;
    for (int end = 0; end < N; end++)
    {
        while (cursor -> next != NULL)
        {
            tmp4 = cursor;
            cursor = cursor -> next;
            free(tmp4);
            if (cursor -> next == NULL)
            {
                break;
            }
        }
    }
    return true;
}
