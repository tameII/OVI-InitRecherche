#include "PointModel.h"


PointModel::PointModel(int nbSlide)
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


}

int PointModel::getNbPointForSlide(int slide){
    return pointToSlide.find(slide)->second.size();
}
