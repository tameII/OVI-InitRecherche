#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QScrollArea>
#include <QPainter>
#include "../Tree.h"

class TreeView : public QScrollArea {
   Q_OBJECT

   private :
      Tree root;

   public :
      TreeView();
      Tree& getTree();
      void draw(QPainter& painter, Tree const& toDraw);

   protected :
      void paintEvent(QPaintEvent* event) override;

};


#endif // TREEVIEWER_H
