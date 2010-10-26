#pragma once

#include "../Direction.h"

class Brain {

    protected:
        virtual void resolvePosition(float movement);
        pos getTargetPosition();
        void setRealColor();
};
