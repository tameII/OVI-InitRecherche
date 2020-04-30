#ifndef OBSERVER_H
#define OBSERVER_H

class Observable;

class Observer {
public :
 Observer() = default;
 virtual ~Observer() = default;
 virtual void update(Observable* obs, void* arg) = 0;
};




#endif //OBSERVER_H
