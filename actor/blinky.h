#pragma once

#include "enemy.h"

class Blinky : public Enemy {

    protected:
        virtual void resolvePosition(float movement);
        pos getTargetPosition();
        void setColor();
};
