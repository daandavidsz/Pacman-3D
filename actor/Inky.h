#pragma once

#include "Enemy.h"
#include "Blinky.h"

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
