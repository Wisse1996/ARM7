#include <stdio.h>  // standard C definitions
#include <string.h>
#include "time.h"
/* functionality of a time object */

// increaseTime will increase the Time object per cento second
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

// timeString wil return a constant string of the Time structure that is passed
// as an argument.
void timeString(struct Time *time, char string[]) {
    // if ((*time).Hours < 10)
    //     sprintf(string, "0%d:%d:%d:%d", (*time).Hours, (*time).Minutes,
    //             (*time).Seconds, (*time).Miliseconds);
    // else if ((*time).Minutes < 10)
    //     sprintf(string, "%d:0%d:%d:%d", (*time).Hours, (*time).Minutes,
    //             (*time).Seconds, (*time).Miliseconds);
    // else if ((*time).Seconds < 10)
    //     sprintf(string, "%d:%d:0%d:%d",  (*time).Hours,  (*time).Minutes,
    //             (*time).Seconds, (*time).Miliseconds);
    // else sprintf(string, "%d:%d:%d:%d", (*time).Hours, (*time).Minutes,
    //                  (*time).Seconds, (*time).Miliseconds);
    sprintf(string, "%02d:%02d:%02d:%02d", (*time).Hours, (*time).Minutes, (*time).Seconds, (*time).Miliseconds);
}

void resetTime(struct Time *time) {
    (*time).Hours = 0;
    (*time).Minutes = 0;
    (*time).Seconds = 0;
    (*time).Miliseconds = 0 ;
}
