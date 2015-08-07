#include <unistd.h>/*sleep*/
#include <stdio.h>
//#include <stdlib.h>
#include "timing.h"

int main(int argc, char **argv) {
    struct timing t;

    printf("timing version: %s\n", timing_get_version());
    timing_start(&t);
    struct timeval tv;
    tv.tv_sec = 1000;
    tv.tv_usec = 101;
    t.start_time = tv;

    tv.tv_sec = 1000000;
    tv.tv_usec = 102;
    t.end_time = tv;
    calc_difference(&t);

    long long i = timeval_diff(NULL, &t.end_time, &t.start_time);
    char *tmp = format_time_diff(&t);
    printf("difference as long long: %lld\t%s\n", i, tmp);

    timing_start(&t);
    sleep(61);
    timing_end(&t);
    printf("time elapsed: %f\n", t.timing_double);
    free(tmp);
}
