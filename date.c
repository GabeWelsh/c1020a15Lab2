#include "date.h"
#include <time.h>
#include <stdio.h>

// compares a and b and returns:
//     -1 if `a` is older than `b` 
//     0 if `b` is the same as `a` 
//     -1 if `b` is older than `a`
// assumes a and b are both valid
// int datecmp(date_t a, date_t b) {
//     // make sure both years are in correct format (not '99 or '85)
//     printf("comparing years\n");    
//     if (a.year < b.year) { // compare years
//         printf("a.year < b.year\n");
//         return -1;
//     } else if (a.year > b.year) {
//         printf("a.year > b.year\n");
//         return 1;
//     } else {
//         if (a.month < b.month) { // compare months
//             printf("a.month < b.month\n");
//             return -1;
//         } else if (a.month > b.month) {
//             printf("a.month > b.month\n");
//             return 1;
//         } else {
//             if (a.day < b.day) { // compare days
//                 printf("a.day < b.day\n");
//                 return -1;
//             } else if (a.day > b.day) {
//                 printf("a.day > b.day\n");
//                 return 1;
//             } else {
//                 printf("same\n");
//                 return 0;
//             }
//         }
//     }
// }

// uses `time.h` to initialize date_t struct
// returns `date_t` with the current date
date_t getDate() {
    time_t time_struct;
    time(&time_struct);
    struct tm *info = localtime(&time_struct);
    date_t date = {info->tm_mon + 1, info->tm_mday, info->tm_year + 1900};
    return date;
}
