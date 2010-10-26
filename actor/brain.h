#pragma once

#include "../direction.h"

class Brain {

    protected:
        virtual void resolvePosition(float movement);
        pos getTargetPosition();
        void setRealColor();
};
