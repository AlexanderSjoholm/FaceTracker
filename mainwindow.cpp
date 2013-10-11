#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageprocess.h"
#include "thresholddialog.h"
#include "webcamdialog.h"
#include "camfaceandeyedetectiondialog.h"
#include "faceclassifierdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuProcess->setDisabled(true);
    imageCounter = 0;

    mainTimer = new QTimer(this);
    connect(mainTimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));
    mainTimer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processFrameAndUpdateGUI(){

}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Images (*.png *.jpg *.jpeg *.bmp)"));

    if(!fileName.isEmpty()){
        imageCounter++;
        activeImage = imageCounter;
        image[imageCounter] = cv::imread(fileName.toLatin1().data());
        QString windowName = QString("Image %1").arg(imageCounter);
        cv::namedWindow(windowName.toLatin1().data());
        cv::imshow(windowName.toLatin1().data(), image[imageCounter]);

        ui->menuProcess->setEnabled(true);
    }
}

void MainWindow::on_actionOpen_recent_triggered()
{
    imageCounter++;
    activeImage = imageCounter;
    image[imageCounter] = cv::imread(QString("C:/Users/Alexander/Desktop/Skogsröjet 2013 - Promo.jpg").toLatin1().data());
    QString windowName = QString("Image %1").arg(imageCounter);
    cv::namedWindow(windowName.toLatin1().data());
    cv::imshow(windowName.toLatin1().data(), image[imageCounter]);

    ui->menuProcess->setEnabled(true);
}

void MainWindow::display(){
    QString windowName = QString("Image %1").arg(activeImage);
    cv::imshow(windowName.toLatin1().data(), image[activeImage]);
}

void MainWindow::on_actionFlip_X_triggered(){
    cv::flip(image[activeImage],image[activeImage], 0);
    display();
}

void MainWindow::on_actionFlip_Y_triggered(){
    cv::flip(image[activeImage],image[activeImage], 1);
    display();
}

void MainWindow::on_actionGray_Scale_triggered(){
    ImageProcess::grayScale(image[activeImage], image[activeImage]);
    display();
}

void MainWindow::on_actionUndo_triggered(){

}

void MainWindow::on_actionThreshold_triggered(){
    ImageProcess::threshold(image[activeImage], image[activeImage]);
    display();
}

void MainWindow::on_actionOpen_Web_Cam_triggered()
{
    WebCamDialog cam;
    cam.exec();
}

void MainWindow::on_actionFace_Eye_Detection_triggered()
{
    FaceClassifierDialog classifierDialog;
    classifierDialog.exec();
}
