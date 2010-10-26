#pragma once

class Timer {
    private:
        long startsec;
    public:
        Timer();
        void start();
        float getSeconds();
};
