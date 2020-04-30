#include "Tree.h"
#include <iostream>

/**
 * @brief Tree::Tree use this to create the root, then use addChildren to add children
 * @param w the widget parent
 * @param p the parent of the tree
 */
Tree::Tree(QWidget *w, Tree* p, int slideNumber) : label(w), parent(p) {
    //placement de root
    label.setGeometry(w->width()/2 - NODE_SIZE/2, 0, NODE_SIZE, NODE_SIZE);
    connect(&label, &QPushButton::clicked, this, &Tree::buttonClicked);
}

void Tree::buttonClicked(){
    std::cout << "Vous venez de cliquer sur un bouton." << std::endl;
    selected(this);
}

/**
 * Deep copy
 * @warning call this only on root
 * @param t the root
 */
Tree::Tree(Tree const& t) : label(t.label.parentWidget()), parent(t.parent){

    label.setGeometry(t.label.geometry());
    for (Tree* c : t){
        children.push_back(new Tree(*c));
    }
    replaceChildren();
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
 * @return *children[index]
 */
Tree& Tree::getChild(int index){
    return *children[index];
}

QPushButton& Tree::getLabel(){
    return label;
}


int const Tree::getSlide() const{
    return slide;
}


void Tree::setParent(Tree *p){
    parent = p;
}

/**
 * @brief Tree::setLabel set the geometry of the label to the geometry of label p
 * @param p the label wich will replace the position and shape of "label"
 *
 */
void Tree::setLabel(QPushButton const& p){
      label.setGeometry(p.geometry());
      replaceChildren();
}

/**
 * @brief Tree::setSelected put the given node to select mode and other to non select mode, need to be used on root first
 *
 */
void Tree::setSelected(Tree *selectedTree){


    for(Tree *c : children) {
        c->setSelected(selectedTree);
    }
}


/**
 * @brief Tree::addChild add *child to the childs of the tree if it exist and this != child
 * @param child a Tree
 */
void Tree::addChild(Tree *child){
    assert(child != nullptr);
    assert(this != child);

    child->parent = this;
    children.push_back(child);
    replaceChildren();
}

/**
 * @brief Tree::replaceChildren place on screen all the children of the node given the position of itself
 */
void Tree::replaceChildren(){

    int nodeWidth = NODE_SIZE;
    int nodeHeight = NODE_SIZE;
    int parentX = label.pos().x() + nodeWidth / 2;
    int parentY = label.pos().y() + nodeHeight / 2;
    int nbChilds = children.size();

    int step = (nbChilds - 1) / 2 * -1;
    int extra = (nbChilds % 2 == 0) ? (-1) : (0);
    bool extraStep = nbChilds % 2 == 0;
    for(Tree *c : children){
         std::cout << step << std::endl;

        int x = parentX + step*(nodeWidth + MARGIN_X) + (nodeWidth / 2 + MARGIN_X / 2) * extra;
        int y = parentY + nodeHeight + MARGIN_Y;
        c->label.setGeometry(x - nodeWidth/2, y - nodeHeight/2, nodeWidth, nodeHeight);
        c->replaceChildren();

        if (step == 0 && extraStep) {
            extraStep = false;
            extra = -extra;
        } else {
           step++;
        }
    }

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
        parent = t.parent;
        for (Tree* c : children) {
          delete c;
        }
        children = t.children;
        setLabel(t.label);
      }

      return *this;
}


Tree const& Tree::operator[](int index) const{
        return *children[index];
}

Tree& Tree::operator[](int index){
        return *children[index];
}


