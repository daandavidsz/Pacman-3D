#pragma once

#include <ctime>
#include <sys/time.h>

class Timer {
    private:
        long startsec;
    public:
        Timer();
        void start();
        float getSeconds();
};
