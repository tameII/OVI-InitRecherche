#include "BorderWidgetQt.h"
#include "AddPointListener.h"

#include <vtkBorderWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkSmartPointer.h>

#include <vtkImageMapper3D.h>

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleImage.h>

#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkImageActor.h>

#include <vtkRendererCollection.h>
#include <vtkPointPicker.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
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
  this->pointModel = new PointModel(0);

  reader = vtkSmartPointer<vtkDICOMImageReader>::New();
  viewer = vtkSmartPointer<vtkImageViewer2>::New();

//  reader->SetDebug(true);
//  viewer->SetDebug(true);



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

//  this->qvtkWidget->GetRenderWindow()->SetDebug(true);

  this->BorderWidget->On();
}


bool BorderWidgetQt::openDicomImage(QString folderPath){
    drawDICOMSeries(folderPath.toUtf8().constData());
    return true;

}

void BorderWidgetQt::drawDICOMSeries(std::string folderDICOM) {
    // Init Reader for alls DICOM files
    reader->SetDirectoryName(folderDICOM.c_str());
    reader->Update();

    viewer->GetImageActor()->SetDisplayExtent(0,429,0,429,0,0);
    viewer->SetInputConnection(reader->GetOutputPort());

    // Link Widget with renderer
    this->viewer->SetRenderWindow(this->qvtkWidget->GetRenderWindow());

    // Viewer initialisation
    viewer->Render();
    viewer->GetRenderer()->ResetCamera();
    viewer->Render();

//    std::cout << "Size : " << *viewer->GetSize() << std::endl;

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

    //TODO trouver une solution pour mettre a jour les points models des parties liées
    //PointModel = new PointModel(maxSlice);
    pointModel->setNewPointModel(maxSlice);
    vtkSmartPointer<AddPointListener> style = vtkSmartPointer<AddPointListener>::New();
    style->setPointModel(pointModel);

    viewer->GetRenderer()->AddActor(actor);


    style->SetDefaultRenderer(viewer->GetRenderer());
    style->SetCurrentRenderer(viewer->GetRenderer());

    viewer->SetupInteractor(this->qvtkWidget->GetInteractor());
    viewer->GetRenderWindow()->GetInteractor()->SetPicker(pointPicker);

    viewer->GetRenderWindow()->GetInteractor()->Render();
    viewer->GetRenderWindow()->GetInteractor()->SetInteractorStyle(style);

    this->qvtkWidget->GetRenderWindow()->Start();

}


/**
 * @brief BorderWidgetQt::sliceSlider set the slice number position to being rendered
 * @param position the slice number
 */
void BorderWidgetQt::sliceSlider(int position) {
    std::cout << "Position : " << position << std::endl;
    drawPointForSlide(position);
    viewer->SetSlice(position);
    pointModel->setCurrentSlide(position);
    viewer->Render();

}

void BorderWidgetQt::drawPointForSlide(int slide){
    //Remove all actor from previous slide
    std::cout << "Current Slide : " << pointModel->getCurrentSlide() << std::endl;
    std::cout << "Number of Actor : " << pointModel->getNbPointForSlide(pointModel->getCurrentSlide()) << std::endl;

    std::list<vtkSmartPointer<vtkActor2D>> actors = pointModel->getPointToSlide().find(pointModel->getCurrentSlide())->second;

    for(vtkSmartPointer<vtkActor2D> actor : actors){
        viewer->GetRenderer()->RemoveActor(actor);
    }

    actors = pointModel->getPointToSlide().find(slide)->second;
    for(vtkSmartPointer<vtkActor2D> actor : actors){
        viewer->GetRenderer()->AddActor(actor);
    }

    //Add actor (if exist) form the target slides
}

void BorderWidgetQt::setPointModel(PointModel *pM){
    pointModel = pM;
}
