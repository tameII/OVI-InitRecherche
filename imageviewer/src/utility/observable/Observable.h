#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <cmath>
#include <cassert>
#include <vector>
#include "../observer/Observer.h"


class Observable
{
public:


    Observable();

    virtual ~Observable() = default;

    bool isChanged() const;


    void add(Observer* o);
//    void remove(Observer* o);
    void clear();

    int getCount() const;

    void notifyAll(void *arg = 0);

    std::vector<Observer*>::iterator begin();
    std::vector<Observer*>::const_iterator begin() const;
    std::vector<Observer*>::const_iterator cbegin() const;

    std::vector<Observer*>::iterator end();
    std::vector<Observer*>::const_iterator end() const;
    std::vector<Observer*>::const_iterator cend() const;


protected:
    void setChanged(bool state);


private:
    bool changed;
    std::vector<Observer*> observers;


};



#endif //OBSERVABLE_H
