#include <QCommandLineParser>
#include <QtWidgets>
#include <QMenuBar>

#include "MainView.h"
#include "../../imageviewer/view/ImageViewer.h"
#include "../../treeviewer/view/TreeViewer.h"


MainView::MainView()
{    
    QCommandLineParser commandLineParser;
    commandLineParser.addHelpOption();
    commandLineParser.addPositionalArgument(ImageViewer::tr("[file]"), ImageViewer::tr("Image file to open."));
    commandLineParser.process(QCoreApplication::arguments());

    if (!commandLineParser.positionalArguments().isEmpty()
        && !imageViewer->loadFile(commandLineParser.positionalArguments().front())) {
        printf("Error loading");
    }
    createActions();

    createGridGroupBox();

    setWindowTitle(tr("ImageViewer"));

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

void MainView::createGridGroupBox()
{
    imageViewer = new ImageViewer();
    treeViewer = new TreeViewer();

    //TODO : Set le PointModel ici

    leftGroupBox = new QGroupBox(tr("TreeViewer"));
    QGridLayout *layoutLeft = new QGridLayout;
    layoutLeft->addWidget(treeViewer, 0, 0);
    leftGroupBox->setLayout(layoutLeft);

    rightGroupBox = new QGroupBox(tr("ImageViewer"));
   QGridLayout *layoutRight = new QGridLayout;
    layoutRight->addWidget(imageViewer, 0, 0);
    rightGroupBox->setLayout(layoutRight);

   QGridLayout *layoutMain = new QGridLayout;
   layoutMain->addWidget(leftGroupBox, 0, 0);
    layoutMain->addWidget(rightGroupBox, 0, 1);
    layoutMain->setColumnStretch(0,30);
    layoutMain->setColumnStretch(1,100);

    layoutMain->setMenuBar(menuBar);


    this->setLayout(layoutMain);

}

void MainView::createActions()
{
    menuBar = new QMenuBar;
    QMenu *fileMenu = menuBar->addMenu(tr("&File"));

    QAction *openAct = fileMenu->addAction(tr("&Open..."), this, &MainView::open);
    openAct->setShortcut(QKeySequence::Open);

    fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));

    QMenu *editMenu = menuBar->addMenu(tr("&Edit"));

    QAction *pasteAct = editMenu->addAction(tr("&Paste"), this, &MainView::paste);
    pasteAct->setShortcut(QKeySequence::Paste);

    QMenu *viewMenu = menuBar->addMenu(tr("&View"));

    zoomInAct = viewMenu->addAction(tr("Zoom &In (25%)"), this, &MainView::zoomIn);
    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    zoomInAct->setEnabled(false);

    zoomOutAct = viewMenu->addAction(tr("Zoom &Out (25%)"), this, &MainView::zoomOut);
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    zoomOutAct->setEnabled(false);

    normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &MainView::normalSize);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);

    viewMenu->addSeparator();

    QMenu *helpMenu = menuBar->addMenu(tr("&Help"));

    helpMenu->addAction(tr("&About"), this, &MainView::about);
    helpMenu->addAction(tr("About &Qt"), &QApplication::aboutQt);
}

void MainView::open(){
   imageViewer->open();
}

void MainView::setImage(int num){
    imageViewer->setImage(num);
}

bool MainView::loadFile(const QString &fileName){
   imageViewer->loadFile(fileName);
    return true;
}

void MainView::paste(){
#ifndef QT_NO_CLIPBOARD
   imageViewer->paste();
#endif // !QT_NO_CLIPBOARD
}

//! [9]
void MainView::zoomIn(){
//    scaleImage(1.25);
//    zoomInAct->setEnabled(scaleFactor < 3.0);
//    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void MainView::zoomOut(){
//    scaleImage(0.8);

//    zoomInAct->setEnabled(scaleFactor < 3.0);
//    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void MainView::normalSize(){
    imageViewer->normalSize();
}

void MainView::about(){
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
               "and QScrollArea to display an image. QLabel is typically used "
               "for displaying a text, but it can also display an image. "
               "QScrollArea provides a scrolling view around another widget. "
               "If the child widget exceeds the size of the frame, QScrollArea "
               "automatically provides scroll bars. </p><p>The example "
               "demonstrates how QLabel's ability to scale its contents "
               "(QLabel::scaledContents), and QScrollArea's ability to "
               "automatically resize its contents "
               "(QScrollArea::widgetResizable), can be used to implement "
               "zooming and scaling features. </p><p>In addition the example "
               "shows how to use QPainter to print an image.</p>"));
}


