#pragma once

#include "Enemy.h"

class Blinky : public Enemy {

    protected:
        virtual void resolvePosition(float movement);
        pos getTargetPosition();
        void setRealColor();
};
