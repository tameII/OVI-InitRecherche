#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QtGui>
#include <QWidget>
#include <QVTKWidget.h>

#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkCamera.h>

#include <itkImage.h>
#include <itkRGBPixel.h>

//#include "itkVTKImageToImageFilter.h"
//#include "itkImageToVTKImageFilter.h"



typedef itk::RGBPixel< unsigned char > RGBPixelType;

typedef itk::Image< unsigned char, 2 > ImageType;
typedef itk::Image< float, 2 > FloatImageType;
typedef itk::Image< RGBPixelType, 2 > RGBImageType;

//typedef itk::VTKImageToImageFilter <ImageType> itkConnectorType;
//typedef itk::ImageToVTKImageFilter <ImageType> vtkConnectorType;
//typedef itk::ImageToVTKImageFilter <RGBImageType> RGBVtkConnectorType;
//typedef itk::ImageToVTKImageFilter <FloatImageType> vtkFloatConnectorType;
class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * Constructor for this ImageWidget
     */
    ImageWidget(QWidget *parent = 0);

    /**
     * Destructor for this ImageWidget
     */
    virtual ~ImageWidget();

    /**
     * load and display an image from file
     */
    void open();

    /**
     * load and display an image from file
     */
    void openWithITK();

    /**
     * Apply a median fiter to the itkImage
     */
    void medianFilter();

    /**
     * Apply a gradient anisotropic diffusion filter to an itkImage
     */
    void gradientAnisotropicDiffusionFilter();

private:
    QVTKWidget *qvtkWidget;
    /** The image displayed for this window */
    ImageType::Pointer itkImage;
    RGBImageType::Pointer rgbItkImage;

    /** The VTK image to display in this window */
    vtkSmartPointer<vtkImageData> vtkImage;
    vtkSmartPointer<vtkImageActor> actor;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderWindowInteractor> interactor;
    vtkSmartPointer<vtkCamera> camera;

signals:

};

#endif // IMAGEWIDGET_H
