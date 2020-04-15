#include "Tree.h"



Tree::Tree(QWidget *w, Tree* p) : label(w), parent(p) {}

/**
 * Deep copy
 * @warning call this only on root
 * @param t the root
 */
Tree::Tree(Tree const& t) : label(t.label.parentWidget()), parent(t.parent){
    for (Tree* c : t){
        children.push_back(new Tree(*c));
    }
}

Tree::~Tree(){
    for (Tree*& c : children){
        delete c;
        c = nullptr;
    }

}

/**
 * @brief getChildren
 * @return the reference of children
 */
std::vector<Tree*> const& Tree::getChildren(){
    return children;
}

/**
 * @return the parent of the actual tree, if it's null then you are at the root
 */
const Tree& Tree::getParent() const{
     assert(parent!=nullptr);
     return *parent;
}

/**
 * @param index the index of the children
 * @return children[index]
 */
const Tree& Tree::getChild(int index) const{
    return *children[index];
}

QPushButton const& Tree::getLabel() const{
    return label;
}

void Tree::setParent(Tree *p){
    parent = p;
}

void Tree::setLabel(QPushButton const& p){
}

void Tree::addChild(Tree *child){
    assert(child != nullptr);
    assert(this != child);

    child->parent = this;
    children.push_back(child);
}

std::vector<Tree*>::iterator Tree::begin(){
    return children.begin();
}
std::vector<Tree*>::const_iterator Tree::begin() const{
    return children.begin();
}
std::vector<Tree*>::const_iterator Tree::cbegin() const{
    return children.cbegin();
}
std::vector<Tree*>::iterator Tree::end(){
    return children.end();
}
std::vector<Tree*>::const_iterator Tree::end() const{
    return children.end();
}
std::vector<Tree*>::const_iterator Tree::cend() const{
    return children.cend();
}

Tree& Tree::operator = (Tree const& t){
    if (this != &t) {

        setLabel(t.label);
        parent = t.parent;
        for (Tree* c : children) {
          delete c;
        }
        children = t.children;
      }
      return *this;
}


Tree const& Tree::operator[](int index) const{
        return *children[index];
}

Tree& Tree::operator[](int index){
        return *children[index];
}


