#ifndef TREEVIEWER_H
#define TREEVIEWER_H

#include <QMainWindow>
#include <QImage>

#include "../QVTree.h"

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE
class TreeViewer : public QMainWindow
{
    Q_OBJECT

public:
    TreeViewer(QWidget *parent = nullptr);
    bool loadFile(const QString &);

private:
    void createActions();
    void createMenus();
    void updateActions();
    bool saveFile(const QString &fileName);
    void setImage(const QImage &newImage);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor = 1;

    QAction *saveAsAct;
    QAction *printAct;
    QAction *copyAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;

};

#endif // TREEVIEWER_H
