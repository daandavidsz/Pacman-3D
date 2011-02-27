#pragma once

#include <stdlib.h>  // exit()
#include <string.h>
#include <iostream>
#include <vector>

class EventObserver {
    
    public:
        virtual void onSignal(std::string name); 

};
