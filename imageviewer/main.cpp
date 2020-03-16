#include <QApplication>
#include "mainview.h"

#include"imageviewer.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkRescaleIntensityImageFilter.h"
#include "QuickView.h"


int main(int argc, char *argv[]){

    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(ImageViewer::tr("Image Viewer"));

    MainView mainView;
    mainView.setWindowTitle("ImageViewer");
    mainView.show();

    return app.exec();
}

