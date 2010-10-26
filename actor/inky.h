#pragma once

#include "enemy.h"
#include "blinky.h"

class Inky : public Enemy {

    private:
        Blinky * blinky;

    protected:
        virtual void resolvePosition(float movement);
        pos getTargetPosition();
        void setRealColor();
        
    public:
        void setBlinky(Blinky * blinky);
};
