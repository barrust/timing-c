#include <unistd.h>/*sleep*/
#include <stdio.h>
//#include <stdlib.h>
#include "timing.h"

int main(int argc, char **argv) {
    Timing t;

    printf("timing version: %s\n", timing_get_version());
    timing_start(&t);
    // modify timing by hand to get a good printout
    struct timeval tv;
    tv.tv_sec = 1000;
    tv.tv_usec = 101;
    t.start_time = tv;

    tv.tv_sec = 1000000;
    tv.tv_usec = 102;
    t.end_time = tv;
    calc_difference(&t);

    long long i = timeval_diff(NULL, &t.end_time, &t.start_time);
    char* tmp = format_time_diff(&t);
    printf("difference as long long: %lld\t%s\n", i, tmp);
    free(tmp);

    // more conventional use case
    timing_start(&t);
    sleep(61);
    timing_end(&t);
    i = timeval_diff(NULL, &t.end_time, &t.start_time);
    tmp = format_time_diff(&t);
    printf("time elapsed: %f\n", timing_get_difference(t));
    printf("difference as long long: %lld\t%s\n", i, tmp);
    free(tmp);

	 timing_start(&t);
	 // code to time here
     for (unsigned long long i = 0; i < 50000000000; i++) {
         // pass
     }
	 timing_end(&t);
	 printf("code completed in %f seconds\n", t.timing_double);
	 char *pretty_output = format_time_diff(&t);
	 printf("code completed in %s (HH:MM:SS.MS.MLS)\n", pretty_output);
	 free(pretty_output);
}
