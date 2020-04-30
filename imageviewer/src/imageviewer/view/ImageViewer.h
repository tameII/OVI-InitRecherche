#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QImage>
#include <QSlider>
#include <QGroupBox>
#include <QGridLayout>
#include <stdio.h>
#include <dirent.h>

#include "../vtkwidget/BorderWidgetQt.h"
#include "../../utility/observer/Observer.h"

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

//! [0]
class ImageViewer : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = nullptr);
    bool loadFile(const QString &);
    void createActions();
    void setImage(int num);
    void setPointModel(PointModel *pM);
    virtual void update(Observable *o, void* arg);

public slots:
    void open();
    void saveAs();
    void copy();
    void paste();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void about();

private:
    void createMenus();
    void updateActions();
    bool saveFile(const QString &fileName);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    QString** listAllFiles(char * filename);
    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QGridLayout *box;
    QSlider *slider;
    QLabel* fileName;
    BorderWidgetQt *border;
    QString ** files ;
    QStringList dcmFiles;
    double scaleFactor = 1;
    int nbFiles;


};

#endif
