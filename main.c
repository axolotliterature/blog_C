#include "blog.h"


//GLOBAL VARIABLES
Blog* postStart;
char* Author;

int main(void) {

    postStart = NULL;

    //get user's name and start the menu
    getName();
    menu();

}