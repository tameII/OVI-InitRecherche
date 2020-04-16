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


void TreeView::paintEvent(QPaintEvent* event) {
    QScrollArea::paintEvent(event);   // super
    //draw lines
    QPainter painter(this->viewport());

    painter.setPen(QPen(Qt::black, 2));
    draw(painter, root);
    painter.end();
}


void TreeView::draw(QPainter& painter, Tree const& toDraw) {
   for (Tree* c : toDraw) {
      //Draw line between child and given root

      int x1 = toDraw.getLabel().pos().x() + toDraw.getLabel().width() / 2;
      int y1 = toDraw.getLabel().pos().y() + toDraw.getLabel().height();
      int x2 = c->getLabel().pos().x() + c->getLabel().width() / 2;
      int y2 = c->getLabel().pos().y();
      painter.drawLine(x1, y1, x2, y2);
      std::cout << x1 << ", " << y1 << " - " << x2 << ", " << y2 << std::endl;
      draw (painter, *c);

   }
}
