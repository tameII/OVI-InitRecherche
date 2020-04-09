#include "BorderWidgetQt.h"
#include "AddPointListener.h"

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

#include <vtkRendererCollection.h>
#include <vtkPointPicker.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>




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


vtkStandardNewMacro(AddPointListener);
// Constructor
BorderWidgetQt::BorderWidgetQt()
{
  this->setupUi(this);

  reader = vtkSmartPointer<vtkDICOMImageReader>::New();
  viewer = vtkSmartPointer<vtkImageViewer2>::New();

  reader->SetDebug(true);
  viewer->SetDebug(true);


  points = vtkSmartPointer<vtkPoints>::New();

//  vtkNew<vtkNamedColors> colors;

//  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;

//  this->qvtkWidget->SetRenderWindow(renderWindow);

  //  renderer->SetBackground(colors->GetColor3d("Black").GetData());

  // Connect VTK with Qt
//  this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

//  vtkSmartPointer<vtkSphereSource> sphereSource =
//    vtkSmartPointer<vtkSphereSource>::New();
//  sphereSource->Update();




  vtkNew<vtkBorderWidget> bw;
  this->BorderWidget = bw;

  this->BorderWidget->SetInteractor(this->qvtkWidget->GetInteractor());

  this->setCentralWidget(this->qvtkWidget);
  this->qvtkWidget->GetRenderWindow()->Start();

  this->qvtkWidget->GetRenderWindow()->SetDebug(true);

  this->BorderWidget->On();
}


bool BorderWidgetQt::openDicomImage(QString folderPath){
    drawDICOMSeries(folderPath.toUtf8().constData());
    return true;

}

void BorderWidgetQt::drawDICOMSeries(std::string folderDICOM) {
    reader->SetDirectoryName(folderDICOM.c_str());

    reader->Update();

    viewer->GetImageActor()->SetDisplayExtent(0,429,0,429,0,0);

    viewer->SetInputConnection(reader->GetOutputPort());

    // lier le widget au rendu
    this->qvtkWidget->SetRenderWindow(this->viewer->GetRenderWindow());

//    viewer->setRenderer(this->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

    // Setup listener
//    viewer->SetupInteractor(this->qvtkWidget->GetInteractor());

    // Initialisation
    viewer->Render();
    viewer->GetRenderer()->ResetCamera();
    viewer->Render();

    std::cout << "Size : " << *viewer->GetSize() << std::endl;

    // Avoir numéro du slide
    minSlice = viewer->GetSliceMin();
    maxSlice = viewer->GetSliceMax();

    vtkSmartPointer<vtkImageCanvasSource2D> drawing = vtkSmartPointer<vtkImageCanvasSource2D>::New();

    vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
    actor->GetMapper()->SetInputConnection(
      drawing->GetOutputPort());
    actor->InterpolateOff();


    vtkSmartPointer<vtkPointPicker> pointPicker =
      vtkSmartPointer<vtkPointPicker>::New();


    vtkSmartPointer<AddPointListener> style = vtkSmartPointer<AddPointListener>::New();

//renderWindowInteractor->SetRenderWindow(this->qvtkWidget->GetRenderWindow());

    viewer->GetRenderer()->AddActor(actor);


    style->SetDefaultRenderer(viewer->GetRenderer());
    style->SetCurrentRenderer(viewer->GetRenderer());

    viewer->SetupInteractor(this->qvtkWidget->GetInteractor());
    viewer->GetRenderWindow()->GetInteractor()->SetPicker(pointPicker);

    viewer->GetRenderWindow()->GetInteractor()->Render();
    viewer->GetRenderWindow()->GetInteractor()->SetInteractorStyle(style);

//    this->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
    this->qvtkWidget->GetRenderWindow()->Start();

}


void BorderWidgetQt::sliceSlider(int position) {
    viewer->PrintSelf(std::cout,vtkIndent(2));
    std::cout << "Size : " << *viewer->GetSize() << std::endl;
    viewer->SetSlice(position);
    viewer->Render();
}
