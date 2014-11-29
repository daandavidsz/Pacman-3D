#pragma once

#include <stdlib.h>  // exit()
#include <string.h>
#include <iostream>
#include <map>
#include <vector>

#include "EventObserver.h"

class EventSystem {

    private:
        static EventSystem * instance;
        std::map<std::string, std::vector<EventObserver*> > observers;
    
    public:
        static EventSystem * getInstance();
        void emit(std::string signal);
        void addObserver(EventObserver * eventObserver, std::string signal);

};
