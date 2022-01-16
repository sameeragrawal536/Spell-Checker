// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include <cs50.h>
#include <unistd.h>
#include "dictionary.h"

char programmer2[45];    // Stores dictionary word for hashing
int ASCII[2];            // Holds ASCII values of 1st characters of a word for hashing
int ASCII2[1];           // Holds ASCIIO values of 1st character of word for hashing, if word is just one character long
int k;                   // Counting variable
bool spelled;            // Whether word is spelled correctly or not
int a = 1;
int j = 0;               // Will store number of words in dictionary

// Definined a node for our linked list. Contains a string and a a pointer to the next node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 676;

// Defining Hash table
node *table[N];

//////////////////////////////////////////////////////////
///////////////////// Hash function //////////////////////
//////////////////////////////////////////////////////////
unsigned int hash(const char *word)
{
    strcpy(programmer2, word);                                         // Store dictionary word in programmer2 variable
    ASCII[0] = 0;
    ASCII[1] = 0;
    ASCII2[0] = 0;
    if ((strlen(programmer2)) >= 2)
    {
        for (int epicly2 = 0; epicly2 < 2; epicly2++)
        {
            if (65 <= ((int) (programmer2[epicly2])) && ((int) (programmer2[epicly2])) <= 90)
            {
                programmer2[epicly2] = programmer2[epicly2] + 32;      // Make first two characters of word lowercase
            }
        }
        
        
        if (97 < ((int) (programmer2[0])) || ((int) (programmer2[0])) > 122)
        {
            return 0;                                                  // If first character is lowercase, do nothing     
        }
        if (97 < ((int) (programmer2[1])) || ((int) (programmer2[1])) > 122)
        {
            return 0;                                                  // If second character is lowercase, do nothing
        }
        
        // Convert ASCII values of characters from numbers between 97 & 122 to numbers between 1 & 26
        for (int epicly = 0; epicly < 2; epicly++)
        {
            if (epicly == 0)
            {
                char c = programmer2[epicly];                          
                ASCII[epicly] = c - 97;                                // ASCII values of a character are from 97 - 122, subtracting 97 makes it 0 - 25
            }
            else
            {
                char c2 = programmer2[epicly];
                ASCII[epicly] = c2 - 97;                               // Do the same with second character of word
            }
        }
           
        return 26*ASCII[0] + ASCII[1];                                 // Return the result of the calculation
    }
    
    //If the word is only one letter long, simply multiply that letter's numerical value (1 to 26) by 26 to find its hash value.
    else
    {
        if (65 <= ((int) (programmer2[0])) && ((int) (programmer2[0])) <= 90)
        {
            programmer2[0] = programmer2[0] + 32;                      // Make letter lowercase 
        }
        char c3 = programmer2[0];
        ASCII2[0] = c3 - 97;                                           // Go from 0 - 25
        return 26*ASCII2[0];                                           // Return result of calculation
    }
    printf("Hashed!\n");
}

//////////////////////////////////////////////////////////
////////////// Loads dictionary into memory //////////////
//////////////////////////////////////////////////////////
bool load(const char *dictionary)
{
    
    FILE *ptr1 = fopen("large", "r");                                      // Opens file containing the dictionary
    if (ptr1 == NULL)
    {
        printf("The very first ptr is null.\n");
        return false;
    }
    
    
    node *list = malloc(sizeof(node));                                    // Malloc enough memory for the first node
    if (list == NULL)
    {
        printf("The very first malloc is null.\n");
        return false;
    }
    
    
    char wordyay2[45];                                                    // Set a char array to the first word of the dictionary
    list -> next = NULL;
    
    
    while((feof(ptr1)) == 0)
    {
        j++;                                                              // Counting the number of words in the dicionary and storing it in a variable
    }
    
    node *arr[j];                                                         // Array of size j which will store memory addresses
    rewind(ptr1);                                                         // Set file reader back to beginning of file
    
    for (k = 0; k < j; k++)                                               // Loop through the dictionary
    {
        node *b = malloc(sizeof(node));                                   // Malloc enough memory for a node
        if (b == NULL)
        {
            printf("We failed to load the word number %i from the dictionary.\n", k);
            return false;
        }
        arr[k] = b;                                                       // Add b, a pointer to memory, to arr
        fscanf(ptr1, "%s", wordyay2);                                     // Read through dictionary file and assign that word to "wordyay2"
        
        
        strcpy((arr[k] -> word), wordyay2);                               // Assigning the word of the dictionary we're on to one of the nodes of the linked list
        arr[k] -> next = NULL; 
    }
    list -> next = arr[0];   
    k = 0;
    
    
    for (k = 0; k < N; k++)                                                 
    {
        table[k] = malloc(sizeof(node));                                 // Create our hash table with 676 "buckets"
    }
    
    for (k = 0; k < j; k++)
    {
      
        unsigned int epic = hash(arr[k] -> word);                        // Hash each word in the dictionary
        
        // If this is the 1st word in this hash bucket
        if ((table[epic] -> next) == NULL)
        {
            table[epic] -> next = arr[k];                                // Make the pointer in the hash table point to this word
        }
        
        // If this hash bucket already has at least one word
        else
        {
            node *tmp = table[epic];                                     // Define a temporary pointer which we will use to travel down the linked list
            while (tmp -> next != NULL)                                  
            {
                tmp = tmp -> next;                                       // Follow the linked list for this hash bucket
                if (tmp -> next == NULL)                                 // If we reach the end of the list
                {
                    tmp -> next = arr[k];                                // Add the word to the end of the list 
                    printf("Word #%i + loaded from dictionary!\n", k);
                    break;
                }
            }
        }
    }
    printf("Loading + hashing complete!\n");
    return true;
}

//////////////////////////////////////////////////////////
/////////////// Actually spell check words ///////////////
//////////////////////////////////////////////////////////
bool check(const char *word)
{
    // Hash the word we are trying to spell check. This way, we only check the word against dictionary words with this hash value to increase efficiency
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

//////////////////////////////////////////////////////////
////////// Returns number of words in dictionary /////////
//////////////////////////////////////////////////////////
unsigned int size(void)
{
    int *ip;
    ip = &j;       // Sets integer pointer address equal to address of j variable
    return *ip;    // Return integer pointer
}

//////////////////////////////////////////////////////////
///////////// Unloads dictionary from memoery ////////////
//////////////////////////////////////////////////////////
bool unload(void)
{
    node *cursor = table[0] -> next;               // Temporary pointer called cursor, set to point to first word in first hash bucket       
    node *tmp4;                      
    for (int end = 0; end < N; end++)              // Loop through each bucket in hash table
    {
        while (cursor -> next != NULL)             // Loop through linked list for this hash bucket
        {
            tmp4 = cursor;                         // Set temporary pointer to same address as cursor            
            free(tmp4);                            // Free memory allocated by cursor pointer
            cursor = cursor -> next;
            if (cursor -> next == NULL)            // If end of linked list for this hash bucket is reached, break from while loop
            {
                break;                           
            }
        }
    }
    return true;
}
