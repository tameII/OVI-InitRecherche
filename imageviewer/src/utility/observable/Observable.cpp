#include "Observable.h"



Observable::Observable(): changed(false){
}


bool Observable::isChanged() const{
    return changed;
}


void Observable::add(Observer* o){
    observers.push_back(o);
}

/**
 * TODO need to finish that.
 * Does not work yet
 */
//void Observable::remove(Observer* o){
//}

/**
 * @brief Observable::clear clear the list of Observer
 */
void Observable::clear(){
    observers.clear();
}

/**
 * @return the number of Observer observing Observable
 */
int Observable::getCount() const{
    return observers.size();
}

/**
 * @brief notifyAll notify all the observer with the given args
 */
void Observable::notifyAll(void *arg){
    if (isChanged()) {
        setChanged(false);
        for(Observer* o : observers) {
            o->update(this, arg);
        }
    }
}

std::vector<Observer*>::iterator Observable::begin(){
    return observers.begin();
}
std::vector<Observer*>::const_iterator Observable::begin() const{
    return observers.begin();
}
std::vector<Observer*>::const_iterator Observable::cbegin() const{
    return observers.cbegin();
}
std::vector<Observer*>::iterator Observable::end(){
    return observers.end();
}
std::vector<Observer*>::const_iterator Observable::end() const{
    return observers.end();
}
std::vector<Observer*>::const_iterator Observable::cend() const{
    return observers.cend();
}

void Observable::setChanged(bool state){
    changed = state;
}
