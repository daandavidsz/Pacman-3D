#include "eventhandler.h"

void EventHandler::onSignal(std::string name) {
}

void EventHandler::addListener(EventHandler * eventHandler) {
    listeners.push_back(eventHandler);
}

void EventHandler::emit(std::string name) {
    for (unsigned int i = 0; i < listeners.size(); i++) {
        listeners[i]->emit(name);
    }
    onSignal(name);
}
