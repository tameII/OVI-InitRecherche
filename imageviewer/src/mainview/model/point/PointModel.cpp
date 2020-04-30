#include "PointModel.h"


PointModel::PointModel(int nbSlide) : Observable()
{
    this->nbSlide = nbSlide;
    pointToSlide = {};
    for(int j =0; j <= nbSlide; j++){
        pointToSlide.insert({j, {}});
    }
}

std::map<int, std::list<vtkSmartPointer<vtkActor2D>>> PointModel::getPointToSlide(){
    return pointToSlide;
}

void PointModel::addPointToSlide(vtkSmartPointer<vtkActor2D> actor){
    std::cout << "Adding new Actor " << std::endl;
    std::cout << "Current Slide :  " << currentSlide << std::endl;
    pointToSlide.find(currentSlide)->second.push_back(actor);
//    std::cout << "Size after adding :  " << actorForslide.size() << std::endl;
    std::cout << "Size after adding :  " << pointToSlide.find(currentSlide)->second.size() << std::endl;

    setChanged(true);
    notifyAll();
}

int PointModel::getNbPointForSlide(int slide){
    return pointToSlide.find(slide)->second.size();
}

/**
 * @brief PointModel::setNewPointModel créé un nouveau pointmodel correspondant aux nombre de slides
 * @param nbSlide le nombre de slide dans l'image fournie
 * note : this  method will maybe disappear soon
 */
void PointModel::setNewPointModel(int nbSlide){
    this->nbSlide = nbSlide;
    pointToSlide = {};
    for(int j =0; j <= nbSlide; j++){
        pointToSlide.insert({j, {}});
    }
    setChanged(true);
    notifyAll();
}
