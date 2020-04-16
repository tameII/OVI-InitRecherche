#ifndef TREE_H
#define TREE_H

#include <cassert>
#include <cmath>
#include <QPushButton>


class Tree
{
public:

    static constexpr int NODE_SIZE = 30;
    static constexpr int MARGIN_X = 16;
    static constexpr int MARGIN_Y = 16;



    Tree(QWidget *w, Tree* parent = nullptr);
    Tree(Tree const& t);

    ~Tree();

    std::vector<Tree*> const& getChildren();
    const Tree& getParent() const;
    const Tree& getChild(int index) const;
    QPushButton const& getLabel() const;

    void setParent(Tree *parent);
    void setLabel(QPushButton const& p);

    void addChild(Tree *t);

    void replaceChildren();

    std::vector<Tree*>::iterator begin();
    std::vector<Tree*>::const_iterator begin() const;
    std::vector<Tree*>::const_iterator cbegin() const;

    std::vector<Tree*>::iterator end();
    std::vector<Tree*>::const_iterator end() const;
    std::vector<Tree*>::const_iterator cend() const;

    Tree& operator = (Tree const& t);
    Tree const& operator[](int index) const;
    Tree& operator[](int index);


private:
    QPushButton label;
    Tree* parent;
    std::vector<Tree*> children;
    //TODO AJouter le numéro de slide
};

#endif // TREE_H
