#pragma once

#include "Enemy.h"

class Pinky : public Enemy {

    protected:
        pos getTargetPosition();
        void setRealColor();
};
