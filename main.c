/* Name: main.c
 * Description: contains `main` and functions for
 *              reporting, buying, and selling stocks
 * Where I learned DIR: https://c-for-dummies.com/blog/?p=3246
*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "list.h"
#include "date.h"
#include "node.h"
#include "stock.h"

int endsWithBin(const char *str) {
    int str_len = strlen(str);
    int suffix_len = strlen(".bin");

    if (str_len < suffix_len) {
        return 0;
    }
    return strncmp(str + str_len - suffix_len, ".bin", suffix_len) == 0;
}


int main() {
    FILE* output;
    DIR* directory = opendir(".");
    struct dirent* dirEntryPtr;
    int userInput = -1; // must be set to enter loop
    int i;
    linked_list_t list;
    node_t* nPtr;
    createList(&list);

    //// use when reading
    // while( (dirEntryPtr = readdir(directory)) != NULL) {
    //     // if d_name ends in .bin
    //     // fopen the file and make sure it's not NULL
    //     // use readStock()
    //     printf("%s\n", dirEntryPtr->d_name);
    // }

    printf("Welcome to YourTrade.com\n");
    while (userInput != 0) {
        printf("Reporting, buying or selling?\n");
        printf("(0=quit, 1=report, 2=buy, 3=sell): ");
        scanf("%d", &userInput);
        switch (userInput) {
            case 0:
                printf("Thank you for trading with YourTrade.com\n");
                break;
            case 1:
                if (directory == NULL) {
                    printf("unable to read directory\n");
                    return 1;
                }
                // report(directory);
                break;
            case 2:
                //buy();
                break;
            case 3:
                //sell()
                break;
            default:
                printf("Enter a valid input.\n");
                break;
        }
    }
    if (nPtr != NULL) {
        free(nPtr);    
    }
    if (output != NULL) {
        fclose(output);
    }
    closedir(directory);

    return 0;
}
