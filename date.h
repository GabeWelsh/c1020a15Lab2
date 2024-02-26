/* Name: date.h
 * Description: define `date_t` struct
*/
#ifndef DATE_T
#define DATE_T

typedef struct {
       int month, day, year;
} date_t;

// returns `date_t` with the current date
date_t getDate();

#endif
