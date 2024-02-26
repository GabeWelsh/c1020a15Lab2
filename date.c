#include "date.h"
#include <time.h>

// uses `time.h` to initialize date_t struct
// returns `date_t` with the current date
date_t getDate() {
    time_t time_struct;
    time(&time_struct);
    struct tm *info = localtime(&time_struct);
    date_t date = {info->tm_mon + 1, info->tm_mday, info->tm_year + 1900};
    return date;
}
