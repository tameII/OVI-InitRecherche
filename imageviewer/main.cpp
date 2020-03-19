#include <QApplication>
#include "mainview.h"

#include"imageviewer.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkRescaleIntensityImageFilter.h"



int main(int argc, char *argv[]){

    ImageType::Pointer image;
    if (argc < 2){
       // std::cerr << "Required: filename" << std::endl;
       // return EXIT_FAILURE;
       image = ImageType::New();
       CreateImage(image);
      }else{
       using ReaderType = itk::ImageFileReader<ImageType>;
       ReaderType::Pointer reader = ReaderType::New();
       reader->SetFileName(argv[1]);
       image = reader->GetOutput();
     }

     using RescaleFilterType = itk::RescaleIntensityImageFilter<ImageType, ImageType>;
     RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
     rescaleFilter->SetInput(image);
     rescaleFilter->SetOutputMinimum(0);
     rescaleFilter->SetOutputMaximum(255);
     rescaleFilter->Update();

    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(ImageViewer::tr("Image Viewer"));

    MainView mainView;
    mainView.setWindowTitle("ImageViewer");
    mainView.show();

    return app.exec();
}

