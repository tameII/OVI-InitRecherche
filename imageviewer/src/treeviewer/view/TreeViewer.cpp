#include "TreeViewer.h"

TreeViewer::TreeViewer(QWidget *parent)
   : QMainWindow(parent){

    setCentralWidget(&view);
}
