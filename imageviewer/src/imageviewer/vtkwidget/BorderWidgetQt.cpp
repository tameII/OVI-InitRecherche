#include "BorderWidgetQt.h"

#include <vtkBorderWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkSmartPointer.h>

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor2D.h>

class BorderCallback : public vtkCommand
{
public:
  BorderCallback()
  {
  }

  static BorderCallback* New()
  {
    return new BorderCallback;
  }

  virtual void Execute(vtkObject* vtkNotUsed(caller), unsigned long, void*)
  {
  }
};

// Constructor
BorderWidgetQt::BorderWidgetQt()
{
  this->setupUi(this);

  reader = vtkSmartPointer<vtkDICOMImageReader>::New();
  viewer = vtkSmartPointer<vtkImageViewer2>::New();

  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;

  this->qvtkWidget->SetRenderWindow(renderWindow);

  //  renderer->SetBackground(colors->GetColor3d("Black").GetData());


  // Connect VTK with Qt
//  this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

  vtkNew<vtkBorderWidget> bw;
  this->BorderWidget = bw;

  this->BorderWidget->SetInteractor(this->qvtkWidget->GetInteractor());
  this->setCentralWidget(this->qvtkWidget);
  this->BorderWidget->On();
}


bool BorderWidgetQt::openDicomImage(QString folderPath){
    drawDICOMSeries(folderPath.toUtf8().constData());
    return true;

}

void BorderWidgetQt::drawDICOMSeries(std::string folderDICOM) {
    reader->SetDirectoryName(folderDICOM.c_str());

    reader->Update();

    viewer->SetInputConnection(reader->GetOutputPort());

    // lier le widget au rendu
    this->viewer->SetRenderWindow(this->qvtkWidget->GetRenderWindow());

    // Setup listener
    viewer->SetupInteractor(this->qvtkWidget->GetInteractor());

    // Initialisation
    viewer->Render();
    viewer->GetRenderer()->ResetCamera();
    viewer->Render();

    // Avoir numéro du slide
    minSlice = viewer->GetSliceMin();
    maxSlice = viewer->GetSliceMax();

    this->qvtkWidget->GetRenderWindow()->Start();

}


void BorderWidgetQt::sliceSlider(int position) {
    viewer->SetSlice(position);
    viewer->Render();
}
