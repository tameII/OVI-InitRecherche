#include "QVTree.h"


QVTree::QVTree(QWidget *parent) : QWidget(parent)
{

    int width=parent->width()*0.7;
    int height=parent->height()*0.7;
    this->setFixedSize(width,height);

    QPushButton *node1 = new QPushButton(parent);
    QPushButton *node2 = new QPushButton(parent);
    QPushButton *node3 = new QPushButton(parent);

    int level = 0;
    int floorSize = 80;
    int widthCorrection = 0;
    int sizeNode = 30;
    node1->setGeometry(width/2 + widthCorrection,level+20,sizeNode,sizeNode);
    level++;
    node2->setGeometry(width/3 + widthCorrection,level*floorSize,sizeNode,sizeNode);
    node3->setGeometry(width - width/3 + widthCorrection,level+floorSize,sizeNode,sizeNode);

    root = new Tree(node1, nullptr, new Tree(node2, new Tree(node3, nullptr, nullptr), nullptr));



}


//EXEMPLE DE PHUC: (Ceci devra être supprimé ultérieurement)
//    QPushButton* l = new QPushButton;
//        l->setText("Hello World!");
//        l->setParent(this);
//        l->setGeometry(50,50,100,100);


