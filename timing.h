/*******************************************************************************
***
***     Author: Tyler Barrus
***     email:  barrust@gmail.com
***
***     Version: 1.0.0
***     Purpose: Provide a simple format to gather timing information
***
***     License:
***
*******************************************************************************/
#ifndef __TIMING_H__
#define __TIMING_H__


#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
    #include <Windows.h>
    #include <stdint.h>     // portable: uint64_t   MSVC: __int64
#else
    #include <sys/time.h>   /* *nix based timing; doesn't support windows */
#endif


#define TIMING_VERSION "1.0.0"
#define TIMING_MAJOR 1
#define TIMING_MINOR 0
#define TIMING_REVISION 0

#define timing_get_version()    (TIMING_VERSION)


struct timing {
    struct timeval end_time;
	struct timeval start_time;
	double timing_double;
} timing;


void timing_start(struct timing *t);
void timing_end(struct timing *t);
char* format_time_diff(struct timing *t);
void calc_difference(struct timing *t); /* only necessary, very occasionally */

#ifdef _WIN32
typedef struct timeval {
    long tv_sec;
    long tv_usec;
} timeval;
int gettimeofday(struct timeval * tp, struct timezone * tzp);
#endif


/* PRIVATE FUNCTIONS */
static long long timeval_diff(struct timeval *difference, struct timeval *end_time, struct timeval *start_time);

/*******************************************************************************
*** PUBLIC FUNCTION DEFINITIONS
*******************************************************************************/
void timing_start(struct timing *t) {
    gettimeofday(&t->start_time, NULL);
	t->end_time.tv_sec = 0;
	t->end_time.tv_usec = 0;
	t->timing_double = 0.0;
}

void timing_end(struct timing *t) {
    gettimeofday(&t->end_time, NULL);
    calc_difference(t);
}

void calc_difference(struct timing *t){
    struct timeval difference;
	timeval_diff(&difference, &t->end_time, &t->start_time);
    t->timing_double = difference.tv_sec + (difference.tv_usec / 1000000.0);
}

char* format_time_diff(struct timing *t) {
	struct timeval difference;
    int digits = 14; // this is everything but the hours
	timeval_diff(&difference, &t->end_time, &t->start_time);
	int s = difference.tv_sec;
	int ms = difference.tv_usec;
	// lazily do the calculations; this could be done in less lines of code
	int hours = s / 3600;
    int n = hours;
    int count = 0;
    while(n!=0) {
        n/=10;
        ++count;
    }
    if (n < 2) {n = 2;}
    digits += n;
	int minutes = (s % 3600) / 60;
	int seconds = (s % 3600) % 60;
	int milliseconds = ms / 1000;
	int microseconds = ms % 1000;
	// put it into a string!
    char* res = malloc(sizeof(char) * (digits + 1));
	sprintf(res, "%02d:%02d:%02d:%03d.%03d", hours, minutes, seconds, milliseconds, microseconds);
    res[digits] = '\0';
    return res;
}


/*******************************************************************************
*** PRIVATE FUNCTIONS
*******************************************************************************/
static long long timeval_diff(struct timeval *difference, struct timeval *end_time, struct timeval *start_time) {
	struct timeval temp_diff;
	// if not passed in, we will use this to do the calculation and
	// then return the number of microseconds
	if(difference == NULL) {
		difference = &temp_diff;
	}
	difference->tv_sec = end_time->tv_sec - start_time->tv_sec;
	difference->tv_usec = end_time->tv_usec - start_time->tv_usec;

	/* Using while instead of if below makes the code slightly more robust. */
	while(difference->tv_usec < 0) {
		difference->tv_usec += 1000000;
		difference->tv_sec -= 1;
	}
	return 1000000LL * difference->tv_sec + difference->tv_usec;
}



/*******************************************************************************
***    Define a gettimeofday function for windows machines
*******************************************************************************/
#ifdef _WIN32
/*
    NOTE: this ignores the timezone information since we don't need it
*/
int gettimeofday(struct timeval * tp, struct timezone * tzp) {
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}
#endif // end defining windows gettimeofday function


#endif /* END OF TIMING.H */
