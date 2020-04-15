#include "QVTree.h"


QVTree::QVTree(QWidget *parent) : QWidget(parent)
{

    int width = this->width();
    int height = this->height();

   // this->setFixedSize(width,height); //seem to be useless here

    QPushButton *TEST = new QPushButton(parent);



//    QPushButton *node1 = new QPushButton(parent);
//    QPushButton *node2 = new QPushButton(parent);
//    QPushButton *node3 = new QPushButton(parent);

    int level = 1;
    int neighborNumber = 0;
    int sizeNode = 30;
    int widthCorrection = sizeNode*2;
    int floorSize = sizeNode;

 TEST->setGeometry(width,height,sizeNode,sizeNode);

//    node1->setGeometry(width + widthCorrection/2,level,sizeNode,sizeNode);
//    level++;
//    neighborNumber++;
//    node2->setGeometry(width,level*floorSize,sizeNode,sizeNode);
//    node3->setGeometry(width + widthCorrection*neighborNumber,level*floorSize,sizeNode,sizeNode);



    root.addChild(new Tree(1));


}


//EXEMPLE DE PHUC: (Ceci devra être supprimé ultérieurement)
//    QPushButton* l = new QPushButton;
//        l->setText("Hello World!");
//        l->setParent(this);
//        l->setGeometry(50,50,100,100);


