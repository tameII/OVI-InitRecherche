#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QScrollArea>
#include <QPainter>
#include "../Tree.h"

class TreeView : public QScrollArea {
   Q_OBJECT

   private slots:
        void buttonClicked(Tree *t);

   private :
      Tree root;
      Tree *selectedNode;
      int slide;
      bool newSlide;

   public :
      TreeView();
      void updateView(int currentSlide);
      Tree& getTree();
      void draw(QPainter& painter, Tree& toDraw);
      void setSelected(Tree *t);



   protected :
      void paintEvent(QPaintEvent* event) override;

};


#endif // TREEVIEWER_H
