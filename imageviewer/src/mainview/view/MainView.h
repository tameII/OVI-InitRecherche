#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "../../imageviewer/view/ImageViewer.h"
#include "../../treeviewer/view/TreeViewer.h"

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

class MainView : public QDialog
{
    Q_OBJECT

public:
    MainView();
    bool loadFile(const QString &);


private slots:
    void open();
    void print();
    void paste();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void about();

private:
    void createGridGroupBox();
    void createActions();
    void updateActions();
    bool saveFile(const QString &fileName);
    void setImage(int num);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QMenuBar *menuBar;
    QGroupBox *leftGroupBox;
    QGroupBox *rightGroupBox;
    ImageViewer *imageViewer;
    TreeViewer *treeViewer;
    double scaleFactor = 1;


    QMenu *fileMenu;
    QAction *exitAction;
    QAction *printAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
};

#endif // MAINVIEW_H


