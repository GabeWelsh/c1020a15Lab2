#include "date.h"
#include <time.h>

// compares a and b and returns:
//     -1 if `a` is older than `b` 
//     0 if `b` is the same as `a` 
//     -1 if `b` is older than `a`
// assumes a and b are both valid
int datecmp(date_t a, date_t b) {
    if (a.year < b.year) { // compare years
        return -1;
    } else if (a.year > b.year) {
        return 1;
    } else { 
        if (a.month < b.month) { // compare months
            return -1;
        } else if (a.month > b.month) {
            return 1;
        } else {
            if (a.day < b.day) { // compare days
                return -1;
            } else if (a.day > b.day) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}

// uses `time.h` to initialize date_t struct
// returns `date_t` with the current date
date_t getDate() {
    time_t time_struct;
    time(&time_struct);
    struct tm *info = localtime(&time_struct);
    date_t date = {info->tm_mon + 1, info->tm_mday, info->tm_year + 1900};
    return date;
}
