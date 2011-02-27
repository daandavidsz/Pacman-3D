#include "EventSystem.h"

EventSystem * EventSystem::instance = new EventSystem();

EventSystem * EventSystem::getInstance() {
    return instance;
}

void EventSystem::emit(std::string signal) {
    if (observers.find(signal) != observers.end()) {
        for (int i = 0; i < observers[signal].size(); i++) {
            observers[signal][i]->onSignal(signal);
        }
    }   
    else {
        std::cout << "Lost signal -> " << signal << "\n";    
    }
}

void EventSystem::addObserver(EventObserver * eventObserver, std::string signal) {
    observers[signal].push_back(eventObserver);
}
