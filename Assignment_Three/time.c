#include <stdio.h>  // standard C definitions
#include <string.h>
#include "time.h"
/* functionality of a time object */

/*** increaseTime will increase the Time object per cento second ***/
void increaseTime(struct Time *time) {
    (*time).Miliseconds++;
    if ((*time).Miliseconds > 99) {
        (*time).Seconds++;
        (*time).Miliseconds = 0;
        if ((*time).Seconds > 59) {
            (*time).Minutes++;
            (*time).Seconds = 0;
            if ((*time).Minutes > 59) {
                (*time).Hours++;
                (*time).Minutes = 0;
            }
        }
    }
}

/*** fill the char array with the structure ***/
void timeString(struct Time *time, char string[]) {
    sprintf(string, "%02d:%02d:%02d:%02d", (*time).Hours, (*time).Minutes,
            (*time).Seconds, (*time).Miliseconds);
}

/*** reset the time structure ***/
void resetTime(struct Time *time) {
    (*time).Hours = 0;
    (*time).Minutes = 0;
    (*time).Seconds = 0;
    (*time).Miliseconds = 0 ;
}
