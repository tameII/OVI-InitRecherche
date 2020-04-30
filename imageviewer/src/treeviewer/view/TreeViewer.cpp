#include "TreeViewer.h"
#include <iostream>

TreeViewer::TreeViewer(QWidget *parent): QMainWindow(parent)
{

    setCentralWidget(&view);

}



void TreeViewer::update(Observable *o, void* arg){
    int currentSlide = dynamic_cast<PointModel&>(*o).getCurrentSlide();  //Permet d'accéder au modèle
    view.updateView(currentSlide);


}


