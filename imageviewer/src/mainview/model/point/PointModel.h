#ifndef POINTMODEL_H
#define POINTMODEL_H


#include <QPushButton>
#include <vtkActor2D.h>
#include <vtkSmartPointer.h>
#include <list>
#include <iterator>

#include "../../utility/observable/Observable.h"

class PointModel : public Observable
{
public:
    PointModel(int nbSlide);
    void addPointToSlide(vtkSmartPointer<vtkActor2D>);
    std::map<int, std::list<vtkSmartPointer<vtkActor2D>>> getPointToSlide();
    int getNbPointForSlide(int sile);
    void setCurrentSlide(int currentSlide){this->currentSlide = currentSlide;}
    int getCurrentSlide(){return this->currentSlide;}
    void setNewPointModel(int nbSlide);
    bool isNew() const;

private:
    int nbSlide;
    int currentSlide = 0;
    std::map<int, std::list<vtkSmartPointer<vtkActor2D>>> pointToSlide;
    bool newModel; //Usefull to know when we had created a new model

};

#endif
