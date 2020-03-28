#ifndef QVTREE_H
#define QVTREE_H

#include <QWidget>
#include <iostream>
#include "tree.h"


class QVTree : public QWidget
{
    Q_OBJECT
public:
    explicit QVTree(QWidget *parent = nullptr);

private:
     Tree *root;

};



#endif // QVTREE_H
