#include <vtkAbstractPicker.h>
#include <vtkActor2D.h>
#include <vtkCoordinate.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

#include <vtkInteractorStyleImage.h>

#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataMapper2D.h>

#include <vtkProperty2D.h>
#include "vtkRegularPolygonSource.h"


#include "../vtkwidget/BorderWidgetQt.h"
#include "../../mainview/model/point/PointModel.h"

class AddPointListener : public vtkInteractorStyleImage
{
  public:
    static AddPointListener* New();
    vtkTypeMacro(AddPointListener, vtkInteractorStyleImage);

    void OnLeftButtonDown()
    {
      //std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0] << " " << this->Interactor->GetEventPosition()[1] << std::endl;
        this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
              this->Interactor->GetEventPosition()[1],
              0,  // always zero.
              this->CurrentRenderer );
      double picked[3];
      this->Interactor->GetPicker()->GetPickPosition(picked);
      //std::cout << "Picked point with coordinate: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;

      this->AddNumber(picked);

      // Forward events
      vtkInteractorStyleImage::OnLeftButtonDown();

      this->Interactor->Render();
    }

    void AddNumber(double p[3])
    {
      std::cout << "Adding marker at " << p[0] << " " << p[1] ;//<< std::endl;

      // normally, with an image you would do
      // double* s = image->GetSpacing();
      // double* o = image->GetOrigin();
      // p[0] = static_cast<int>( (p[0] - o[0]) / s[0] + 0.5 );
      p[0] = static_cast<int>( p[0] + 0.5 );
      p[1] = static_cast<int>( p[1] + 0.5 );

      std::cout << " -> " << p[0] << " " << p[1] << std::endl;

      // Create an actor for the text
      vtkSmartPointer<vtkRegularPolygonSource> polygonSource =
          vtkSmartPointer<vtkRegularPolygonSource>::New();

        //polygonSource->GeneratePolygonOff(); // Uncomment this line to generate only the outline of the circle
        polygonSource->SetNumberOfSides(50);
        polygonSource->SetRadius(5);
        polygonSource->SetCenter(0, 0, 0);

      double* bounds = polygonSource->GetOutput()->GetBounds();
      //transform the polydata to be centered over the pick position
      double center[3] = {0.5*(bounds[1]+bounds[0]), 0.5*(bounds[3]+bounds[2]), 0.0 };

      vtkSmartPointer<vtkTransform> trans = vtkSmartPointer<vtkTransform>::New();
      trans->Translate( -center[0], -center[1], 0 );
      trans->Translate( p[0], p[1], 0 );

      vtkSmartPointer<vtkTransformPolyDataFilter> tpd = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
      tpd->SetTransform( trans );
      tpd->SetInputConnection(  polygonSource->GetOutputPort() );

      // Create a mapper
      vtkSmartPointer<vtkPolyDataMapper2D> mapper = vtkSmartPointer<vtkPolyDataMapper2D>::New();
      vtkSmartPointer<vtkCoordinate> coordinate = vtkSmartPointer<vtkCoordinate>::New();
      coordinate->SetCoordinateSystemToWorld();
      mapper->SetTransformCoordinate( coordinate );
      mapper->SetInputConnection( tpd->GetOutputPort() );

      vtkSmartPointer<vtkActor2D> actor = vtkSmartPointer<vtkActor2D>::New();
      actor->SetMapper( mapper );
      actor->GetProperty()->SetColor( 1, 0, 0 ); // yellow

//      PointModel::addPointToSlide(this->CurrentImageNumber, actor);

      this->CurrentRenderer->AddViewProp(actor);

      pointModel->addPointToSlide(actor);

    }

    void setPointModel(PointModel *pM){
        this->pointModel = pM;
    }

    private:
        PointModel *pointModel = nullptr;

};
