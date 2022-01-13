# Spell-Checker
A spell checker created in C. Given a txt file, it will compare each word of the file against a separate dictionary, and print all the words it cannot find in the dictionary, indicating that these words are "misspelled". This was part of the Harvard CS50 Introduction to Computer Science course assignment for Week 5. 

The program incorporates a hash function and a linked list, both made from scratch, in order to organize the words in the dictionary, making the program more efficient. 

The program works by first, hashing each word in a special "dictionary" file. Next, the program looops through the text we are spell checking. For each word in the text, we hash the word, then go through all the words in the dictionary which also have that hash value. If, at any point, a word in the dictionary and the word we are spell checking match, we can conclude that the word is spelled correctly. If we reach the end of the words with that hash value and have still not found a match, we conclude that the word was spelled incorrectly.

When running the program, run "speller.c", inputing the name of the txt file you would like for it to check. An example run would be: "./ speller constitution.txt", if "constitution.txt" were the text you are trying to spell check.

The files "wells.txt" and "wells key.txt" provide a sample text and key, respectively, to run the program on.

The "dictionary.o" and "dictionary.h" files allow the program to access a dictionary. The "dictionary.c" program was what was actually written by me, and defines the methods "hash", "load", "check", "size", and "unload", which are then called on the "speller.c" program. All the files other than "dictionary.c" were provided to me when I started the assignment.

MakeFile:

clang -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o speller.o speller.c

clang -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o dictionary.o dictionary.c

clang -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -o speller speller.o dictionary.o -lm

