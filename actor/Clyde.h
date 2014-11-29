#pragma once

#include "Enemy.h"

class Clyde : public Enemy {

    protected:
        pos getTargetPosition();
        void setRealColor();
};
