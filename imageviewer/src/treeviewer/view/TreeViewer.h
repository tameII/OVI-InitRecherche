#ifndef TREEVIEWER_H
#define TREEVIEWER_H

#include <QMainWindow>
#include "TreeView.h"

class TreeViewer : public QMainWindow
{
    Q_OBJECT

public:
    TreeViewer(QWidget *parent = nullptr);

private:
    TreeView view;

};

#endif // TREEVIEWER_H
