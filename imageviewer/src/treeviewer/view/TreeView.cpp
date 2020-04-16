#include "TreeView.h"
#include <iostream>

TreeView::TreeView() : root(this) {
        //Initialize the tree
        Tree* child1 = new Tree(this, &root);
        Tree* child2 = new Tree(this, child1);
        Tree* child3 = new Tree(this, child2);
        Tree* child4 = new Tree(this, child3);
        Tree* child5 = new Tree(this, child4);
        Tree* child6 = new Tree(this, child5);
        Tree* child7_1 = new Tree(this, child6);
        Tree* child7_2 = new Tree(this, child6);
        Tree* child7_3 = new Tree(this, child6);
        Tree* child8 = new Tree(this, child7_1);
        Tree* child9 = new Tree(this, child8);
        Tree* child10 = new Tree(this, child9);
        Tree* child11 = new Tree(this, child10);
        Tree* child12 = new Tree(this, child11);
        Tree* child13 = new Tree(this, child12);
        Tree* child14 = new Tree(this, child13);

       child13->addChild(child14);

       child12->addChild(child13);

       child11->addChild(child12);

       child10->addChild(child11);

       child9->addChild(child10);

       child8->addChild(child9);

       child7_1->addChild(child8);

//        //Problème lié au placement naïf:
//        child7_1->addChild(new Tree(this));

//        child7_2->addChild(new Tree(this));
//        child7_2->addChild(new Tree(this));
//        child7_2->addChild(new Tree(this));

//        child7_3->addChild(new Tree(this));
//        //Fin problème lié au placement naïf

        child6->addChild(child7_1);
        child6->addChild(child7_2);
        child6->addChild(child7_3);

        child5->addChild(child6);

        child4->addChild(child5);

        child3->addChild(new Tree(this));
        child3->addChild(child4);

        child2->addChild(new Tree(this));
        child2->addChild(new Tree(this));
        child2->addChild(new Tree(this));
        child2->addChild(child3);

        child1->addChild(child2);
        child1->addChild(new Tree(this));
        child1->addChild(new Tree(this));
        child1->addChild(new Tree(this));
        child1->addChild(new Tree(this));
        child1->addChild(new Tree(this));

        root.addChild(child1);
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
