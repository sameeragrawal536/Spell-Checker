// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include <cs50.h>
#include <unistd.h>
#include "dictionary.h"

// Represents a node in a hash table
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
    
    //If the word is only one letter long, simply multiply that letter's numerical value (1 to 26) by 26 to find its hash value.
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
    // Opens file containing the dictionary, or the list of all English words which our program will check the words of the txt file against.
    FILE *ptr1 = fopen("large", "r");
    if (ptr1 == NULL)
    {
        printf("The very first ptr is null.\n");
        return false;
    }
    
    //Malloc enough memory for the first node
    node *list = malloc(sizeof(node));
    if (list == NULL)
    {
        printf("The very first malloc is null.\n");
        return false;
    }
    
    // Set a char array to the first word of the dictionary
    char wordyay2[45];
    list -> next = NULL;
    fscanf(ptr1, "%s", wordyay2);
    
    // Basically counting the number of words in the dicionary and storing it in a variable called j
    while((feof(ptr1)) == 0)
    {
        fscanf(ptr1, "%s", wordyay2);
        j++;
    }
    
    /* Creates an array of memory addresses, loads each word from the dictionary file into its own malloc, and stores the memory address to that allocated memory
    in that array. */
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
        
        // Assigning each word in the dictionary to one of the nodes
        strcpy((arr[k] -> word), wordyay2);
        arr[k] -> next = NULL;
    }
    list -> next = arr[0];
    k = 0;
    
    // Create our hash table with 676 "buckets"
    for (k = 0; k < N; k++)
    {
        table[k] = malloc(sizeof(node));
    }
    int as = 0;
    for (k = 0; k < j; k++)
    {
        // Hash each word in the dictionary
        unsigned int epic = hash(arr[k] -> word);
        
        // If this is the first word in this hash "bucket", make the pointer in the hash table point to this word
        if ((table[epic] -> next) == NULL)
        {
            table[epic] -> next = arr[k];
        }
        
        // If not, follow the linked list for that hash "bucket" until you reach its end, at which point add the new word and make the previous pointer point to it
        else
        {
            node *tmp = table[epic];
            while (tmp -> next != NULL)
            {
                tmp = tmp -> next;
                if (tmp -> next == NULL)
                {
                    tmp -> next = arr[k];
                    printf("Word #%i + loaded from dictionary!\n", k);
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
    // Hash the word we are trying to spell check
    unsigned int programmer = hash(word);
    
    // Access the hash "bucket" which this word would have belonged to
    node *tmp2 = table[programmer];
    
    // The longest word in the dictionary is 45 characters long, so only check the word if it is less than 45 characters long
    if (strlen(programmer2) <= 45)
    {
        // Loop through all the words in the linked list belonging to this specific hash "bucket"
        while (tmp2 -> next != NULL)
        {
            // Make all letters in the word lowercase
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
            
            // To make spell checking slightly more efficient, only check if the word we're checking and the dictionary word we're currently on have the same length
            if (strlen(tmp2 -> word) == strlen(programmer2))
            {
                // If the words match, we are done checking this word
                if ((strncmp((tmp2 -> word), (programmer2), (strlen(programmer2)))) == 0)
                {
                    spelled = true;
                    break;
                }
                
                // If the words do not match, go to the next dictionary word in this hash "bucket"
                else
                {
                    tmp2 = tmp2 -> next;
                }
            }
            
            // If the lengths of the words aren't the same, we move on to the next dictionary word in this hash "bucket" without even comparing.
            else
            {
                tmp2 = tmp2 -> next;
            }
        }
        
        // If we reach the last word in this hash "bucket"
        if (tmp2 -> next == NULL)
        {
            // If the lengths of the words are the same, we check
            if  (strlen(tmp2 -> word) == strlen(programmer2))
            {
                // If the words match, we're done checking the word
                if ((strncmp(tmp2 -> word, programmer2, strlen(programmer2))) == 0)
                {
                    spelled = true;
                }
                
                /* If they do not match, we can conclude the word we're checking is spelled incorrectly, because there are no more words in this hash "bucket" to
                check */
                else
                {
                    //printf("The word %s is spelled wrong.\n", programmer2);
                    spelled = false;
                }
            }
            
            // If the lengths don't even match, we can conclude that the word we're checking is spelled incorrectly.
            else
            {
                //printf("The word %s is spelled wrong.\n", programmer2);
                spelled = false;
            }
        }
    }
    
    // If the length of the word is more than 45 characters, we know it is spelled wrong.
    else
    {
        spelled = false;
    }
    
    return spelled;
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
