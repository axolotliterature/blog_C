/*
Andrew Hansen
5/6/2022
CS251
HW5 Blog Post List

DESCRIPTION
This program guides the user through dynamically adding blog posts in the form of structs. The user can also print out how many types of each blog there are, or print out blogs by type, title, date, or print all blogs. The user can also dynamically remove blog entries. On exit, the program frees up all structs created with malloc, as well as global variables.

*/

/*
Repair log:

5/15/2022
added proper malloc safety/error checks
clarified function descriptions
globalized postStart == null error messages

5/17/2022
fixed memory leak at freeMemory function: function now set to free the strings within the struct before freeing the struct itself
fixed memory leak at removePost of same nature of above
streamlined removePost function, changed argument variable postToDel into char array[] of size BUFFER rather than char* allocated with malloc so that the variable in memory is not a leak liability (I think?) No reason to malloc just for a temp variable if it's passing the contents anyway, and not actually utilizing the pointer.

New errors-
On exit: free() pointer error
dual free calls I think?

on remove post: segmentation fault
on remove post 3rd entry: munmap_chunk(): invalid pointer

-free() has to see the exact thing malloc created.
-check that the strings are assigned via strcpy and not "string = 'string'"
-perhaps rewrite allocation to first malloc on currentPos->string, use a temp variable to scanf, then strcpy contents over to the malloc'd variable. this should retain the original pointer from the malloc and relieve the munmap error

on exit, 1 entry: segmentation fault
on exit, 2 entries: seg fault

5/20

changed getTitle to first malloc currentPos->Title at Blog creation, then scanf to temp variable for user input and strcpy over to currentPos->Title. This fixes the munmap pointer error.


(NEED TO) executed similar fixes to getType and getEntry functions, and reset free() calls.
For getType, since function already returns a string, return into another temp var, then strcpy over into currentPos->Type.

actually, in getType, set up iteration loop before selection choice, replace returns with strcpy into currentPos


*/

//is exit(num) used in proper context?




#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER 100
#define ENTRYBUFFER 500

#pragma once

//==================================== STRUCTURES AND GLOBAL VARIABLES

typedef struct Blog Blog;
struct Blog {
    int Date;
    char* Title;
    char* Type; //(Diary, Hobby, Journalism, Art)
    char* Entry;
    Blog* next;
};

extern struct Blog* postStart;
extern char* Author;

//==================================== FUNCTION PROTOTYPES

void addPost();
void entryCount();
int removePost(char* postTitle);
void printAll();
void printDate(int postDate);
void printTitle(char* postTitle);
void printType(char* postType);
void freeMemory();

//======================== My Functions

void menu();
void getName();
int getDate();
void getTitle();
char* getType();
char* getEntry();


#endif