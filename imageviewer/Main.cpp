#include <QApplication>
#include "MainView.h"
#include"ImageViewer.h"
#include "BorderWidgetQt.h"

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkRescaleIntensityImageFilter.h"

using ImageType = itk::Image<unsigned char, 2>;
static void CreateImage(ImageType * const image);

int main(int argc, char *argv[]){

    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(ImageViewer::tr("Image Viewer"));

    MainView mainView;
    mainView.setWindowTitle("ImageViewer");
    mainView.show();

    return app.exec();
}


void CreateImage(ImageType * const image){
  // Create an image with 2 connected components
  ImageType::IndexType corner = { { 0, 0 } };

  ImageType::SizeType size;
  unsigned int        NumRows = 200;
  unsigned int        NumCols = 300;
  size[0] = NumRows;
  size[1] = NumCols;

  ImageType::RegionType region(corner, size);

  image->SetRegions(region);
  image->Allocate();

  // Make a square
  for (unsigned int r = 40; r < 100; r++)
  {
    for (unsigned int c = 40; c < 100; c++)
    {
      ImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, 15);
    }
  }
}

