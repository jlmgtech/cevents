#ifndef sleep_ms_h
#define sleep_ms_h
#include <stdlib.h>

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void float_sleep(float seconds){ // cross-platform sleep function
    int milliseconds = (int)(seconds * 1000.0F);
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000)
        sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}

#endif

float random_fraction() {
    float r = (float)rand();
    float max = (float)RAND_MAX;
    return r / max;
}
