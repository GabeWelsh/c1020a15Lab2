/* Name: date.h
 * Description: define `date_t` struct
*/
#ifndef DATE_T
#define DATE_T

typedef struct {
       int month, day, year;
} date_t;

int datecmp(date_t a,date_t b);
date_t getDate();

#endif
