/* Name: date.h
 * Description: define `date_t` struct
*/
#ifndef DATE_T
#define DATE_T

typedef struct {
       int month, day, year;
} date_t;

// compares a and b and returns:
//     -1 if `a` is older than `b` 
//     0 if `b` is the same as `a` 
//     -1 if `b` is older than `a`
// assumes a and b are both valid
// int datecmp(date_t a, date_t b);
// uses `time.h` to initialize date_t struct
// returns `date_t` with the current date
date_t getDate();

#endif
