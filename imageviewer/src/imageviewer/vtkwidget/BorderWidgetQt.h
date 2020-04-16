#ifndef BorderWidgetQt_H
#define BorderWidgetQt_H

#include <vtkSmartPointer.h>
#include <QMainWindow>
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>

#include "../../mainview/model/point/PointModel.h"

class vtkBorderWidget;

#include "ui_BorderWidgetQt.h"

class BorderWidgetQt : public QMainWindow, private Ui::BorderWidgetQt
{
  Q_OBJECT
public:

  // Constructor/Destructor
  BorderWidgetQt();
  ~BorderWidgetQt() {}
  bool openDicomImage(QString folderPath);
  void openDICOMFolder();
  void sliceSlider(int position);
  void addPointToPointList();

private slots:
    void drawDICOMSeries(std::string folderDICOM);
    void drawPointForSlide(int slide);

//    void on_sliderSlices_sliderMoved(int posicion);

private:
//    Ui::BorderWidgetQt *ui;
    vtkSmartPointer<vtkDICOMImageReader> reader;
    vtkSmartPointer<vtkImageViewer2> viewer;
    int minSlice;
    int maxSlice;
    vtkSmartPointer<vtkBorderWidget> BorderWidget;
    PointModel *pointModel;
};

#endif
