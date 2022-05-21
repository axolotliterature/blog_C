#include "blog.h"

//main menu UI handles majority of this program; loops for user selection, returning to the menu until exit is selected
void menu() {
    int choice = 0;
    while (1) {
//MENU UI
        printf("\n~=~=~=~=~=~=~=~=~=~=~=\n\n");
        printf("Hello %s, what would you like to do?\n", Author);
        printf("\n1. Add Post \n2. Count Entries \n3. Print Post(s) \n4. Remove Post \n5. Exit Program \n");
        printf("\n~=~=~=~=~=~=~=~=~=~=~=\n\n");
        scanf(" %d", &choice);
        printf("\n");

//MENU SELECTIONS
        if (choice == 1) { //Add post
            addPost();
        } 
        else if (choice == 2) { //Count Entries
            entryCount();           
        } 
        else if (choice == 3) { //Print Posts -- SUBMENU
            if (postStart == NULL) { //check that start isn't null
                printf("!=========================!\n");
                printf("There are no blog post entries...\nPlease begin by adding a blog post.\n");
                printf("!=========================!\n");
                while (getchar() != '\n'); //clear buffer
            } else if (postStart != NULL) { //If blog start exists, continue
                int selection = 0;
                printf("\n\n-=-=-=-=-=-=-=-=-=-=-=\n");
                printf("Which entries would you like to print:\n1. Print by Date\n2. Print by Title\n3. Print by Type\n4. Print all entries\n");
                printf("-=-=-=-=-=-=-=-=-=-=-=\n\n");
                scanf(" %d", &selection);
                while (1) {
                    if (selection == 1) { //print by date
                        printDate(getDate());
                        break;
                    } else if (selection == 2) { //print by title
                        char titlename[BUFFER];
                        printf("Title of post: ");
                        scanf(" %s", titlename);
                        printTitle(titlename);
                        break;
                    } else if (selection == 3) { //print by type                      
                        printType(getPrintType());
                        break;
                    } else if (selection == 4) { //print all
                        printAll();
                        break;
                    } else {
                        printf("Invalid input of ( %d ), please enter a valid number\n", selection);
                        while (getchar() != '\n'); //clear buffer
                        scanf(" %d", &selection);
                    }
                }
            }
    
        } 
        else if (choice == 4) { //Remove Post
            int result;
            char postToDel[BUFFER];
            printf("Please enter the title of the post you would like to remove...\n");
            scanf(" %s", postToDel);
            result = removePost(postToDel);
            if (result == 0) {
                //success
                printf("Successfully removed blog post titled %s.\n", postToDel);
            } else if (result == 1) {
                //failed to find
                printf("Failed to find post titled %s.\n", postToDel);
                printf("Please check spelling and try again.\n");
            } else if (result == 2) {
                //iteration loop failed
                printf("Error: Iteration failure\n");
            }
        } 
        else if (choice == 5) { //Exit Program
            // Quits out of the menu, frees memory and ends the program.
            freeMemory();
            exit(0);
        }
        else { //wrong input error, reprompts for input
            printf("Invalid input of ( %d ), please enter a valid number\n", choice);
            while (getchar() != '\n'); // clear input buffer of erroneous input
        }
    }

}

//If postStart is null, creates start and fills with user prompted data. 
//If postStart exists, iterates through Blog* list, adds ->next Blog* to last node, moves to new node and fills with user prompted data
void addPost() {
    if (postStart == NULL) { //if postStart is NULL, creates first item
        postStart = (Blog*)malloc(sizeof(Blog));
        if (postStart == NULL) { //malloc error check
            printf("Failed to create start of Blog list, quitting...\n");
            exit(-1);
        }

        //fills new blog info with user input, sets next pointer to NULL
        postStart->Date = getDate(); //get date of blog
            while (postStart->Date == -1) {
                postStart->Date = getDate();
            }
        postStart->Title = (char*)malloc(sizeof(char)*BUFFER);
        getTitle();
        postStart->Type = (char*)malloc(sizeof(char)*BUFFER);
        getType();

        postStart->Entry = getEntry(); //Get blog Entry
        postStart->next = NULL; //Set next pointer to null
    } else { //start at beginning of blog list, iterate through to the end (NULL)

        Blog* currentPos = postStart;
        while (currentPos->next != NULL) {
            currentPos = currentPos->next;
        }

        //create new blog
        currentPos->next = (Blog*)malloc(sizeof(Blog));
        if (currentPos == NULL) { //malloc error check
            printf("Failed to create new blog end of list, quitting...\n");
            exit(-2);
        }

        //moves to new blog, fills new blog with user input, sets next pointer to NULL
        currentPos = currentPos->next;
        currentPos->Date = getDate();
            while (currentPos->Date == -1) {
                currentPos->Date = getDate();
            }
        currentPos->Title = (char*)malloc(sizeof(char)*BUFFER);
        getTitle();
        currentPos->Type = (char*)malloc(sizeof(char)*BUFFER);
        getType();
        
        currentPos->Entry = getEntry();
        currentPos->next = NULL;
    }
}

//iterates through blog list, counts each blog type encountered, also adds a total count
void entryCount() {
    int diary = 0, hobby = 0, journ = 0, art = 0, total = 0;

    //check first post is not null
    if (postStart == NULL) {
        printf("\n!=================================!\n");
        printf("There are no blog post entries...\nPlease begin by adding a blog post.\n");
        printf("!=================================!\n");
        while (getchar() != '\n'); //clear buffer
        return;
    }

    //iterates through Blog list, counts each entry type
    Blog* currentPos = postStart;
    while (currentPos != NULL) {
        if (strcmp(currentPos->Type, "Diary") == 0) {
            diary++;
        } else if (strcmp(currentPos->Type, "Hobby") == 0) {
            hobby++;
        } else if (strcmp(currentPos->Type, "Journalism") == 0) {
            journ++;
        } else if (strcmp(currentPos->Type, "Art") == 0) {
            art++;
        }
        currentPos = currentPos->next;
    }

    total = diary + hobby + journ + art;

    printf("\n\n~=~=~=~=~=~=~=~=~=~=~=\n\n");
    printf("Diary Entries   : %d\n", diary);
    printf("Hobby Entries   : %d\n", hobby);
    printf("Journal Entries : %d\n", journ);
    printf("Art Entries     : %d\n", art);
    printf("\n");
    printf("Total Entries   : %d\n", total);
    // printf("\n~=~=~=~=~=~=~=~=~=~=~=\n");
    // return;

}

//iterates through Blog list, compares Blog->Title to postTitle
//if match found: frees matching blog and returns 0 
//if no match found: returns 1 
//if neither is true for some stupid reason??: returns 2
int removePost(char* postTitle) {
    Blog* currentPos = postStart;
    Blog* prevPos = currentPos;
    int delCount = 0;

    //check first node->Title, if match to postTitle, rotates postStart to be the next node and frees the former postStart node
    if (strcmp(postStart->Title, postTitle) == 0) {
        Blog* temp = postStart;
        postStart = postStart->next;
        free(temp->Title);
        // free(temp->Type);
        // free(temp->Entry);
        free(temp);
        delCount++;
    }



    while (currentPos != NULL) {


        //checks current position->title, if match - point previous->next to current->next and free current position
        if (strcmp(currentPos->Title, postTitle) == 0) {
            prevPos->next = currentPos->next;
            free(currentPos->Title);
            // free(currentPos->Type);
            // free(currentPos->Entry);
            free(currentPos);
            delCount++;
        }
        //continue iterating through list
        prevPos = currentPos;
        currentPos = currentPos->next;
    }
    if (delCount > 0) {
        return 0;
    } else if (delCount == 0) {
        return 1;
    }
    return 2;
    
}

//iterates through blog* list and prints each entry
void printAll() {
    Blog* currentPos = postStart;

    //iterate through full list, printing each entry
    while (currentPos != NULL) {
        printf("\n~*~*~*~*~*~*~*~*~*~*~\n\n");
        printf("Title: %s\n", currentPos->Title);
        printf("Date: %d\n", currentPos->Date);
        printf("Type: %s\n", currentPos->Type);
        printf("====================\n");
        printf("Entry: \n%s\n", currentPos->Entry);
        currentPos = currentPos->next;
    }
    printf("\n~*~*~*~*~*~*~*~*~*~*~*\n\n");
    while (getchar() != '\n'); //clear buffer
}

//iterates through blog* list, prints each entry that matches date argument
void printDate(int postDate) {
    Blog* currentPos = postStart;
    int count = 0;

    //iterate through full list, compare date value, print if dates match
    while (currentPos != NULL) {
        if (currentPos->Date == postDate) {
            printf("\n\n~*~*~*~*~*~*~*~*~*~*=\n\n");
            printf("Title: %s\n", currentPos->Title);
            printf("Date: %d\n", currentPos->Date);
            printf("Type: %s\n", currentPos->Type);
            printf("====================\n");
            printf("Entry: \n%s\n", currentPos->Entry);
            count++;
        }
        currentPos = currentPos->next;
    }
    if (count > 0) {
        printf("\n~*~*~*~*~*~*~*~*~*~*~*\n\n");
    }
    if (count == 0) {
        printf("Search found no entries on this date.\n");
    }
    while (getchar() != '\n'); //clear buffer
}

//iterates through blog* list, prints each entry that matches strcmp title argument
void printTitle(char* postTitle) {
    Blog* currentPos = postStart;
    int count = 0;
    //iterate through full list, strcmp title value, print if matches
    while (currentPos != NULL) {
        if (strcmp(currentPos->Title, postTitle) == 0) {
            printf("\n\n~*~*~*~*~*~*~*~*~*~*=\n\n");
            printf("Title: %s\n", currentPos->Title);
            printf("Date: %d\n", currentPos->Date);
            printf("Type: %s\n", currentPos->Type);
            printf("====================\n");
            printf("Entry: \n%s\n", currentPos->Entry);
            count++;
        }
        currentPos = currentPos->next;
    }
    if (count > 0) {
        printf("\n~*~*~*~*~*~*~*~*~*~*~*\n\n");
    }
    if (count == 0) {
        printf("No entries found titled %s\n", postTitle);
    }
    while (getchar() != '\n'); //clear buffer
}

//iterates through blog* list, prints each entry that matches strcmp type argument
void printType(char* postType) {
    Blog* currentPos = postStart;
    int count = 0;
    //iterate through full list, strcmp type value, print if matches
    while (currentPos != NULL) {
        if (strcmp(currentPos->Type, postType) == 0) {
            printf("\n\n~*~*~*~*~*~*~*~*~*~*=\n\n");
            printf("Title: %s\n", currentPos->Title);
            printf("Date: %d\n", currentPos->Date);
            printf("Type: %s\n", currentPos->Type);
            printf("====================\n");
            printf("Entry: \n%s\n", currentPos->Entry);
            count++;
        }
        currentPos = currentPos->next;
    }
    if (count > 0) {
        printf("\n~*~*~*~*~*~*~*~*~*~*~*\n\n");
    }
    if (count == 0) {
        printf("No entries found of type %s\n", postType);
    }
    while (getchar() != '\n'); //clear buffer
}

//iterates through blog* list, freeing space of each previous blog
//then also frees Author and postStart
void freeMemory() {
    Blog* currentPos = postStart;
    Blog* prevPos = currentPos;

    while (currentPos != NULL) {
        prevPos = currentPos;
        currentPos = currentPos->next;
        free(prevPos->Title);
        free(prevPos->Type);
        free(prevPos->Entry);
        free(prevPos);
        }
    if (Author != NULL) {
        free(Author);
    }
    if (postStart != NULL) {
        free(postStart);
    }

}

//allocates for Author global variable, prompts user to input name, stores as Author global variable 
void getName() {
    Author = (char*)malloc(sizeof(char)*BUFFER);
    if (Author == NULL) { //malloc error check
        printf("Failed to allocate: Author");
        exit(-1);
    }
    printf("Please enter your name: ");
    scanf(" %[^\n]", Author); 
    while (getchar() != '\n'); // clear buffer
}

//prompts user for date input in format mm/dd/yyyy, changes ints to strings to concatenate without backslash, converts back to int, return int as mmddyyyy
//allocates for string variable, returns address of string
int getDate() {
    int mm, dd, yyyy, date;
    char s1[3], s2[3], s3[5], s4[9];
    printf("Please enter the date: MM/DD/YYYY: ");
    scanf(" %d%*c%d%*c%d", &mm, &dd, &yyyy); //ignores char between date ints

    //if date value or format is way off, prints error, dumps buffer and returns -1
    if (mm < 0 || mm > 12 || dd < 0 || dd > 31 || yyyy < 1900 || yyyy > 9999) {
        printf("\nERROR: Please use the suggested date format.\n");
        while (getchar() != '\n'); // clear buffer
        return -1;
    }

    //moves separate ints to strings...
    sprintf(s1, "%d", mm);
    sprintf(s2, "%d", dd);
    sprintf(s3, "%d", yyyy);
    //contatenates strings together...
    strcpy(s4, s1);
    strcat(s4, s2);
    strcat(s4, s3);    
    //converts string back to integer
    date = atoi(s4);

    while (getchar() != '\n'); // clear buffer
    return date;
}

//prompts user for title of blog, iterates through Blog list to most recent Blog, scanf user input to temp string, strcpy temp string into currentPos->Title
//allocate memory for Title before calling getTitle()
void getTitle() {
    char titlename[BUFFER];
    Blog* currentPos = postStart;
    while (currentPos->next != NULL) {
        currentPos = currentPos->next;
    }
    printf("Title of post: ");
    scanf(" %s", titlename);
    strcpy(currentPos->Title, titlename);
}

//prompts the user for blog type via list of selections (input = int), iterates through Blog list to most recent Blog, strcpy exact string needed into currentPos->Type, reduces user error
//allocate memory for Type before calling getType
void getType() {
    int selection;
    Blog* currentPos = postStart;

    while (currentPos->next != NULL) { //iterate through to most recent Blog position
        currentPos = currentPos->next;
    }

    printf("\n\n-=-=-=-=-=-=-=-=-=-=-=\n\n");
    printf("Type of entry:\n1. Diary\n2. Hobby\n3. Journalism\n4. Art\n");
    printf("\n-=-=-=-=-=-=-=-=-=-=-=\n\n");

    scanf(" %d", &selection);

    while (1) {
        if (selection == 1) { //Type = Diary
            while (getchar() != '\n'); //clear buffer before return
            strcpy(currentPos->Type, "Diary");
        } else if (selection == 2) { //Type = Hobby
            while (getchar() != '\n'); //clear buffer before return
            strcpy(currentPos->Type, "Hobby");
        } else if (selection == 3) { //Type = Journalism
            while (getchar() != '\n'); //clear buffer before return
            strcpy(currentPos->Type, "Journalism");
        } else if (selection == 4) { //Type = Art
            while (getchar() != '\n'); //clear buffer before return
            strcpy(currentPos->Type, "Art");
        } else { //Wrong input, reprompt user input and repeat loop
            printf("Invalid input of ( %d ), please enter a valid number\n", selection);
            while (getchar() != '\n'); // clear buffer
            scanf(" %d", &selection);
        }
    }
   
}

//prompts the user for blog type via list of selections (input = int), returns exact string needed, reduces user error
//similar function to getType(), except this function returns the string, rather than strcpy the string into the Blog
char* getPrintType() {
    int selection;

    printf("\n\n-=-=-=-=-=-=-=-=-=-=-=\n\n");
    printf("Type of entry:\n1. Diary\n2. Hobby\n3. Journalism\n4. Art\n");
    printf("\n-=-=-=-=-=-=-=-=-=-=-=\n\n");

    scanf(" %d", &selection);

    while (1) {
        if (selection == 1) { //Type = Diary
            while (getchar() != '\n'); //clear buffer before return
            return "Diary";
        } else if (selection == 2) { //Type = Hobby
            while (getchar() != '\n'); //clear buffer before return
            return "Hobby";
        } else if (selection == 3) { //Type = Journalism
            while (getchar() != '\n'); //clear buffer before return
            return "Journalism";
        } else if (selection == 4) { //Type = Art
            while (getchar() != '\n'); //clear buffer before return
            return "Art";
        } else { //Wrong input, reprompt user input and repeat loop
            printf("Invalid input of ( %d ), please enter a valid number\n", selection);
            while (getchar() != '\n'); // clear buffer
            scanf(" %d", &selection);
        }
    }
   
    
}

//prompts user for blog entry (size of ENTRYBUFFER), allocates for string variable, 
// returns address of string - scanf whole string entry until newline
char* getEntry() {
    char* entry = (char*)malloc(sizeof(char)*ENTRYBUFFER);
    if (entry == NULL) { //malloc error check
        printf("Failed to allocate: Entry");
        exit(-1);
    }
    printf("Entry: ");
    scanf(" %[^\n]", entry);
    while (getchar() != '\n'); //clear buffer
    return entry;
}
