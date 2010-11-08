#pragma once

#include "Enemy.h"

class Blinky : public Enemy {

    protected:
        pos getTargetPosition();
        void setRealColor();
};
