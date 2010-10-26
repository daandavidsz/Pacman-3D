#pragma once

#include <stdlib.h>  // exit()
#include <string.h>
#include <iostream>
#include <vector>

class EventHandler {
    
    std::vector<EventHandler*> listeners;
    
    public:
        virtual void onSignal(std::string name); 
        void emit(std::string signal);
        void addListener(EventHandler * eventHandler);

};
