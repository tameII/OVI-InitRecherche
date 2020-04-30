#include "TreeView.h"
#include <iostream>

TreeView::TreeView() : root(this), slide(-1) {

    connect(&root, &Tree::selected, this, &TreeView::buttonClicked);
    selectedNode = &root;
}

//Créé deux nouveaux noeud si la currentSlide n'a pas changé
void TreeView::updateView(int currentSlide){

    if(currentSlide == slide){ //currentSlide does not change, we create two node
        Tree* child1 = new Tree(this, selectedNode, currentSlide);
        Tree* child2 = new Tree(this, selectedNode, currentSlide);

        connect(child1, &Tree::selected, this, &TreeView::buttonClicked);
        connect(child2, &Tree::selected, this, &TreeView::buttonClicked);

        selectedNode->addChild(child2);
        selectedNode->addChild(child1);

        child1->getLabel().show();
        child2->getLabel().show();

        //Il est possible de choisir arbitrairement le nouveau noeud selectionné
       // setSelected(child2);
    }else{
        slide = currentSlide;
    }
}



void TreeView::buttonClicked(Tree *t){
    setSelected(t);

}
void TreeView::setSelected(Tree *t){
    selectedNode = t;
    getTree().setSelected(t);
}

Tree& TreeView::getTree() {
  return root;
}

/**
 * @brief TreeView::paintEvent override of the class paintEvent of QPainter
 * @param event used like the QPainter parameter
 */
void TreeView::paintEvent(QPaintEvent* event) {
    QScrollArea::paintEvent(event);   // super
    //draw lines
    QPainter painter(this->viewport());
    painter.setPen(QPen(Qt::black, 2));
    draw(painter, root);
    painter.end();
}

/**
 * @brief TreeView::draw side method who hold the algorithm for drawing
 * @param painter the Picasso responsible to draw beautiful lines
 * @param toDraw The Tree you want to draw
 */
void TreeView::draw(QPainter& painter, Tree& toDraw) {
   for (Tree* c : toDraw) {
      //Draw line between child and given root
      int x1 = toDraw.getLabel().pos().x() + toDraw.getLabel().width() / 2;
      int y1 = toDraw.getLabel().pos().y() + toDraw.getLabel().height();
      int x2 = c->getLabel().pos().x() + c->getLabel().width() / 2;
      int y2 = c->getLabel().pos().y();
      painter.drawLine(x1, y1, x2, y2);
      draw (painter, *c);
   }   
}

