#ifndef TREEVIEWER_H
#define TREEVIEWER_H

#include <QMainWindow>
#include "TreeView.h"
#include "../utility/observer/Observer.h"
#include "../mainview/model/point/PointModel.h"

class TreeViewer : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    TreeViewer(QWidget *parent = nullptr);
    virtual void update(Observable *o, void* arg);

private:
    TreeView view;

};

#endif // TREEVIEWER_H
