
struct Time {
	// hours as in 60 minutes
	int Hours;
	// minutes as in 60 second
	int Minutes;
	// seconds as in seconds
	int Seconds;
	// milliseconds as in miliseconds
	int Miliseconds;
};


void increaseTime(struct Time *time);
void timeString(struct Time *time, char string[]);
void resetTime(struct Time *time);

/*This is a time declaration struct that can save a time value in the following
 * structure "00:00:00:00 as hh:mm:ss:mm*/

