#include "ImageViewer.h"

#include <QApplication>
#include <QClipboard>
//#include <QColorSpace>
#include <QDir>
#include <QFileDialog>
#include <QImageReader>
#include <QImageWriter>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QMimeData>
#include <QPainter>
#include <QScreen>
#include <QScrollArea>
#include <QScrollBar>
#include <QStandardPaths>
#include <QStatusBar>
#include <QDebug>


#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#endif

ImageViewer::ImageViewer(QWidget *parent) : QMainWindow(parent), imageLabel(new QLabel), scrollArea(new QScrollArea){

    QPalette pal = palette();
    //If ressoucre not exist or empty => crash
    border = new BorderWidgetQt();

    scrollArea->setBackgroundRole(QPalette::Base);

    scrollArea->setVisible(true);
    setCentralWidget(scrollArea);

    box = new QGridLayout;
    slider = new QSlider(Qt::Horizontal, scrollArea);
    fileName = new QLabel(scrollArea);

    fileName->setText("");
    fileName->setMargin(1);
    box->addWidget(border,0,0);
    box->setRowStretch(0,85);
    box->addWidget(fileName,1,0,Qt::AlignCenter);
    box->setRowStretch(1,5);
    box->addWidget(slider,2,0);
    box->setRowStretch(2,10);
    box->setSpacing(0);
    box->setMargin(0);
    box->setContentsMargins(0,0,0,0);


    scrollArea->setLayout(box);

    slider->setRange(0, 0);
    connect(slider, &QSlider::valueChanged, this, &ImageViewer::setImage);
    slider->setEnabled(false);

}

bool ImageViewer::loadFile(const QString &folderPath){
    QDir directory(folderPath);
    dcmFiles = directory.entryList(QStringList() << "*.dcm" << "*.DCM",QDir::Files);
    nbFiles = dcmFiles.size();
    std::cout << "main function %d" << nbFiles  << std::endl;
    if (nbFiles <= 0) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Aucune image dicom détecté dans ce dossier."));
        return false;
    }

    border->openDicomImage(folderPath);

    slider->setRange(0, nbFiles-1);

    slider->setEnabled(true);

    fileName->setText(dcmFiles.at(0));

    return true;
}

void ImageViewer::setImage(int num){
    std::cout << nbFiles;
    fileName->setText(dcmFiles.at(num));
    border->sliceSlider(num);
}

bool ImageViewer::saveFile(const QString &fileName){
    QImageWriter writer(fileName);

    if (!writer.write(image)) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName)), writer.errorString());
        return false;
    }
    const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
    statusBar()->showMessage(message);
    return true;
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode){
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setOption(QFileDialog::ShowDirsOnly, false);
}

void ImageViewer::open(){
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void ImageViewer::saveAs(){
    QFileDialog dialog(this, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

    while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first())) {}
}

void ImageViewer::print(){
    Q_ASSERT(imageLabel->pixmap());
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printer, this);
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
#endif
}

void ImageViewer::copy(){
#ifndef QT_NO_CLIPBOARD
    QGuiApplication::clipboard()->setImage(image);
#endif // !QT_NO_CLIPBOARD
}

#ifndef QT_NO_CLIPBOARD
static QImage clipboardImage(){
    if (const QMimeData *mimeData = QGuiApplication::clipboard()->mimeData()) {
        if (mimeData->hasImage()) {
            const QImage image = qvariant_cast<QImage>(mimeData->imageData());
            if (!image.isNull())
                return image;
        }
    }
    return QImage();
}
#endif // !QT_NO_CLIPBOARD

void ImageViewer::paste(){
#ifndef QT_NO_CLIPBOARD
    const QImage newImage = clipboardImage();
    if (newImage.isNull()) {
        statusBar()->showMessage(tr("No image in clipboard"));
    } else {
        //setImage(newImage);
        setWindowFilePath(QString());
        const QString message = tr("Obtained image from clipboard, %1x%2, Depth: %3")
            .arg(newImage.width()).arg(newImage.height()).arg(newImage.depth());
        statusBar()->showMessage(message);
    }
#endif // !QT_NO_CLIPBOARD
}

//! [9]
void ImageViewer::zoomIn(){
    scaleImage(1.25);
}

void ImageViewer::zoomOut(){
    scaleImage(0.8);
}

void ImageViewer::normalSize(){
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void ImageViewer::about(){
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
               "and QScrollArea to display an image. QLabel is typically used "
               "for displaying a text, but it can also display an image. "
               "QScrollArea provides a scrolling view around another widget. "
               "If the child widget exceeds the size of the frame, QScrollArea "
               "automatically provides scroll bars. </p><p>The example "
               "demonstrates how QLabel's ability to scale its contents "
               "(QLabel::scaledContents), and QScrollArea's ability to "
               "automatically resize its contents "
               "(QScrollArea::widgetResizable), can be used to implement "
               "zooming and scaling features. </p><p>In addition the example "
               "shows how to use QPainter to print an image.</p>"));
}

void ImageViewer::scaleImage(double factor){
//    Q_ASSERT(imageLabel->pixmap());
//    scaleFactor *= factor;
//    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

//    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
//    adjustScrollBar(scrollArea->verticalScrollBar(), factor);
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor){
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
