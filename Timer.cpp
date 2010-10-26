#include "Timer.h"

Timer::Timer() {
    start();
}

void Timer::start() {
    struct timeval start;
    gettimeofday(&start, NULL);
    startsec = start.tv_sec;            
}

float Timer::getSeconds() {
    struct timeval start;
    gettimeofday(&start, NULL);
    
    return (start.tv_sec - startsec) + start.tv_usec/1000000.0;
}
