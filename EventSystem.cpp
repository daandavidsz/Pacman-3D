#include "EventSystem.h"

EventSystem * EventSystem::instance = NULL;

EventSystem * EventSystem::getInstance() {
    if (!instance) {
        instance = new EventSystem();
    }
    return instance;
}

void EventSystem::emit(std::string signal) {
    if (observers.find(signal) != observers.end()) {
        for (int i = 0; i < observers[signal].size(); i++) {
            observers[signal][i]->onSignal(signal);
        }
    }   
}

void EventSystem::addObserver(EventObserver * eventObserver, std::string signal) {
    std::vector<EventObserver*> list = observers[signal]; 
    list.push_back(eventObserver);
}
