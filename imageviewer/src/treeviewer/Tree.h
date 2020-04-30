#ifndef TREE_H
#define TREE_H

#include <cassert>
#include <cmath>
#include <QPushButton>
#include <QWidget>

class Tree : public QObject
{
    Q_OBJECT

private slots:
    void buttonClicked();

signals:
    void selected(Tree *t);

public:

    static constexpr int NODE_SIZE = 30;
    static constexpr int MARGIN_X = 16;
    static constexpr int MARGIN_Y = 16;



    Tree(QWidget *w, Tree* parent = nullptr, int slideNumber = 0);
    Tree(Tree const& t);

    ~Tree();
    std::vector<Tree*> const& getChildren();
    const Tree& getParent() const;
    Tree& getChild(int index);
    QPushButton& getLabel();
    int const getSlide() const;


    void setParent(Tree *parent);
    void setLabel(QPushButton const& p);
    void setSelected(Tree *select);

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
    int slide;
    Tree* parent;
    std::vector<Tree*> children;


};

#endif // TREE_H
