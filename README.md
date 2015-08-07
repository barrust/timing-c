# timing-c

###Purpose:
This header utility is to be able to quickly provide timing functionality to standard c code. It is designed to be benificial to me as I am tired of re-writting the same type of functionality. I hope it is benificial to others.

###License:
Copyright 2015 Licensed under the MIT License 

###Usage:
```
#include "timing.h"
...
struct timing t;

timing_start(&t);
// code to time here
timing_end(&t);
printf("time elapsed: %f\n", t.timing_double);
```
