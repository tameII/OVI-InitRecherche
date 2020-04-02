#include "BorderWidgetQt.h"

#include <vtkBorderWidget.h>
#include <vtkCommand.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkVersion.h>


#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>

#include <vtkNamedColors.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <sstream>
#include <vtkSphereSource.h>

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

  vtkNew<vtkRenderer> renderer;
  renderer->SetBackground(colors->GetColor3d("Black").GetData());


  // Connect VTK with Qt
  this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

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

    // Avoir numéro du slide
    minSlice = viewer->GetSliceMin();
    maxSlice = viewer->GetSliceMax();

}


void BorderWidgetQt::sliceSlider(int position) {
    viewer->SetSlice(position);
    viewer->Render();
}
