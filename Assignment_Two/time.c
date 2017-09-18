#include <string.h>
#include "time.h"
/* functionality of a time object */

// increaseTime will increase the Time object per cento second
struct *Time increaseTime(time *Time) {
    time.Miliseconds ++;
    if (&time.Miliseconds < 99) {
        &time.Seconds ++;
        &time.Miliseconds = 0;
        if (&time.Seconds < 60) {
            &time.Minutes ++;
            &time.Seconds = 0;
            if (&time.minutes) < 60;
                &time.Hours ++
                &rime.Minutes = 0;
        }
    }
    return time;
}

// timeString wil return a constant string of the Time structure that is passed
// as an argument.
const char * timeString(time *Time) {
    const char string = "00:00:00:00";
    sprintf(string, "%d:%d:%d:%d", &time.Hours, &time.Minutes, &time.Seconds, &time.Miliseconds);
    return *string;
}

struct *Time resetTime(time *Time){
    &time.Hours = 0;
    &time.Minutes = 0;
    &time.Seconds = 0;
    &time.Miliseconds = 0 ;
    return time;
}
