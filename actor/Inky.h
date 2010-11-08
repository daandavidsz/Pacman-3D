#pragma once

#include "Enemy.h"
#include "Blinky.h"

class Inky : public Enemy {

    private:
        Blinky * blinky;

    protected:
        pos getTargetPosition();
        void setRealColor();
        
    public:
        void setBlinky(Blinky * blinky);
};
