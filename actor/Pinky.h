#pragma once

#include "Enemy.h"

class Pinky : public Enemy {

    protected:
        virtual void resolvePosition(float movement);
        pos getTargetPosition();
        void setRealColor();
};
