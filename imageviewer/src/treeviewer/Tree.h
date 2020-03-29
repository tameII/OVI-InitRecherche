#ifndef TREE_H
#define TREE_H


#include <QPushButton>

class Tree
{
public:
    Tree(QPushButton *label, Tree *next, Tree *child);


private:
    QPushButton *label;
    Tree *next;
    Tree *child;
};

#endif // TREE_H
