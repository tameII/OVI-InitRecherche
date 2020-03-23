#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "ImageViewer.h"
#include "TreeViewer.h"

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

private:
    void createMenu();
    void createGridGroupBox();
    void createActions();

    QMenuBar *menuBar;
    QGroupBox *leftGroupBox;
    QGroupBox *rightGroupBox;
    ImageViewer imageViewer;
    TreeViewer treeViewer;

    QMenu *fileMenu;
    QAction *exitAction;
};

#endif // MAINVIEW_H


