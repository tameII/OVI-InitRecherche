#include "Tree.h"

Tree::Tree(QPushButton *label, Tree *next, Tree *child)
{
  this->label = label;
  this->next = next;
  this->child = child;



}
