#pragma once

#include "enemy.h"

class Pinky : public Enemy {

    protected:
        virtual void resolvePosition(float movement);
        pos getTargetPosition();
        void setRealColor();
};
