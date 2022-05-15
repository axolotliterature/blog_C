/*
Andrew Hansen
5/6/2022
CS251
HW5 Blog Post List

DESCRIPTION
This program guides the user through dynamically adding blog posts in the form of structs. The user can also print out how many types of each blog there are, or print out blogs by type, title, date, or print all blogs. The user can also dynamically remove blog entries. On exit, the program frees up all structs created with malloc, as well as global variables.

*/

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

//======================== My Added Functions

void menu();
void getName();
int getDate();
char* getTitle();
char* getType();
char* getEntry();


#endif