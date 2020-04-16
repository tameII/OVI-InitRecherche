#include "TreeView.h"
#include <iostream>

TreeView::TreeView() : root(this) {
        //Initialize the tree
        Tree* child1 = new Tree(this, &root);
        child1->addChild(new Tree(this));
        child1->addChild(new Tree(this));
        child1->addChild(new Tree(this));
        child1->addChild(new Tree(this));
        root.addChild(child1);
        root.addChild(new Tree(this));
        root.addChild(new Tree(this));
        root.addChild(new Tree(this));
        root.addChild(new Tree(this));
        root.addChild(new Tree(this));


}

Tree& TreeView::getTree() {
  return root;
}

/**
 * @brief TreeView::paintEvent override of the class paintEvent of QPainter
 * @param event used like the QPainter parameter
 */
void TreeView::paintEvent(QPaintEvent* event) {
//    QScrollArea::paintEvent(event);   // super
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
void TreeView::draw(QPainter& painter, Tree const& toDraw) {
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
