#include <QCommandLineParser>
#include <QtWidgets>
#include <QMenuBar>

#include "mainview.h"
#include "imageviewer.h"
#include "treeviewer.h"


MainView::MainView()
{    
    QCommandLineParser commandLineParser;
    commandLineParser.addHelpOption();
    commandLineParser.addPositionalArgument(ImageViewer::tr("[file]"), ImageViewer::tr("Image file to open."));
    commandLineParser.process(QCoreApplication::arguments());

    if (!commandLineParser.positionalArguments().isEmpty()
        && !imageViewer.loadFile(commandLineParser.positionalArguments().front())) {
        printf("Error loading");
    }
    createMenu();

    createGridGroupBox();

    setWindowTitle(tr("ImageViewer"));

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

void MainView::createGridGroupBox()
{
    ImageViewer *imageViewer = new ImageViewer();
    TreeViewer *treeViewer = new TreeViewer();

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

void MainView::createMenu()
{
    menuBar = new QMenuBar;
    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);
    connect(exitAction, &QAction::triggered, this, &QDialog::accept);
}

void MainView::createActions()
{

    QMenu *fileMenu = menuBar->addMenu(tr("&File"));

//    QAction *openAct = fileMenu->addAction(tr("&Open..."), this, &ImageViewer::open);
//    openAct->setShortcut(QKeySequence::Open);

//    saveAsAct = fileMenu->addAction(tr("&Save As..."), this, &ImageViewer::saveAs);
//    saveAsAct->setEnabled(false);

//    printAct = fileMenu->addAction(tr("&Print..."), this, &ImageViewer::print);
//    printAct->setShortcut(QKeySequence::Print);
//    printAct->setEnabled(false);

    fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));

    QMenu *editMenu = menuBar->addMenu(tr("&Edit"));

//    copyAct = editMenu->addAction(tr("&Copy"), this, &ImageViewer::copy);
//    copyAct->setShortcut(QKeySequence::Copy);
//    copyAct->setEnabled(false);

//    QAction *pasteAct = editMenu->addAction(tr("&Paste"), this, &ImageViewer::paste);
//    pasteAct->setShortcut(QKeySequence::Paste);

    QMenu *viewMenu = menuBar->addMenu(tr("&View"));

//    zoomInAct = viewMenu->addAction(tr("Zoom &In (25%)"), this, &ImageViewer::zoomIn);
//    zoomInAct->setShortcut(QKeySequence::ZoomIn);
//    zoomInAct->setEnabled(false);

//    zoomOutAct = viewMenu->addAction(tr("Zoom &Out (25%)"), this, &ImageViewer::zoomOut);
//    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
//    zoomOutAct->setEnabled(false);

//    normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &ImageViewer::normalSize);
//    normalSizeAct->setShortcut(tr("Ctrl+S"));
//    normalSizeAct->setEnabled(false);

    viewMenu->addSeparator();

//    fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &ImageViewer::fitToWindow);
//    fitToWindowAct->setEnabled(false);
//    fitToWindowAct->setCheckable(true);
//    fitToWindowAct->setShortcut(tr("Ctrl+F"));

    QMenu *helpMenu = menuBar->addMenu(tr("&Help"));

//    helpMenu->addAction(tr("&About"), this, &ImageViewer::about);
    helpMenu->addAction(tr("About &Qt"), &QApplication::aboutQt);
}

