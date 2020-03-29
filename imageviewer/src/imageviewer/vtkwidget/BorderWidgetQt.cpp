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
    //      vtkBorderWidget *borderWidget =
    //          reinterpret_cast<vtkBorderWidget*>(caller);
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
    // Asigna carpeta de donde obtener las imágenes DICOM
    reader->SetDirectoryName(folderDICOM.c_str());
    reader->Update();

    // Enlaza el input del viewer al output del reader
    viewer->SetInputConnection(reader->GetOutputPort());

    // Enlaza el widget con el viewer
    this->viewer->SetRenderWindow(this->qvtkWidget->GetRenderWindow());

//    this->qvtkWidget->set
    // Añade interactor al viewer
    viewer->SetupInteractor(this->qvtkWidget->GetInteractor());

    // Inicializa
    viewer->Render();

    // Obtiene el número de slices
    minSlice = viewer->GetSliceMin();
    maxSlice = viewer->GetSliceMax();

    this->BorderWidget->SetInteractor(this->qvtkWidget->GetInteractor());
    this->setCentralWidget(this->qvtkWidget);
    this->BorderWidget->On();

    // Actualiza labels de la GUI
//    ui->sliderSlices->setMinimum(minSlice);
//    ui->sliderSlices->setMaximum(maxSlice);
//    ui->labelSlicesNumber->setText(QString::number(maxSlice - minSlice));
//    ui->labelFolderName->setText(QString::fromStdString(folderDICOM));
}


void BorderWidgetQt::sliceSlider(int position) {
    viewer->SetSlice(position);
    viewer->Render();
}
