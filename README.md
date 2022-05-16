# blog_C
Basic blogging system made for an Intro to C course

TO DO

6/8 removePost:
-1 Does not free the internal strings of the struct
-1 Logic for the check is wrong, will only check the first node as the next else if is:
else if (strcmp(currentPos->Title, postTitle) != 0) {
            return 1;
        }
So if the first doesn't match, then it quits out as a failure.

3/5 Free Memory:
-2 Does not free internal string memory of structs

before freeing the struct, clear out the internal strings.
Otherwise they will float off into the ether, still occupying memory but inaccessible.

free(current->Title);
free(current->Type);
free(current->Entry);
free(current);

1/5 malloc/calloc Safety:
Very few to no checks if the calls failed.

getDate can be improved greatly