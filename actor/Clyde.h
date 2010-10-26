#pragma once

#include "Enemy.h"

class Clyde : public Enemy {

    protected:
        virtual void resolvePosition(float movement);
        pos getTargetPosition();
        void setRealColor();
};
