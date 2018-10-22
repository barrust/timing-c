# timing-c

### Purpose:
This header utility is to be able to quickly provide timing functionality to standard c code. It is designed to be beneficial to me as I am tired of re-writting the same type of functionality. I hope it is beneficial to others.

### License:
Copyright 2015 Licensed under the MIT License

### Usage:
```c
#include <stdio.h>
#include <stdlib.h>
#include "timing.h"
Timing t;

timing_start(&t);
// code to time here
timing_end(&t);
printf("time elapsed: %f\n", t.timing_double);

// get to elapsed time elements easily
printf("hours:        %d\n", timing_get_hours(t));
printf("minutes:      %d\n", timing_get_minutes(t));
printf("seconds:      %d\n", timing_get_seconds(t));
printf("milliseconds: %d\n", timing_get_milliseconds(t));
printf("microseconds: %d\n", timing_get_microseconds(t));

// get to a pretty print version
char* output = format_time_diff(&t);
printf("pretty output: %s\n", output);
free(output);

```
