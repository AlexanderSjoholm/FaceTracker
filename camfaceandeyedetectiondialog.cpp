#include "camfaceandeyedetectiondialog.h"
#include "ui_camfaceandeyedetectiondialog.h"

CamFaceAndEyeDetectionDialog::CamFaceAndEyeDetectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CamFaceAndEyeDetectionDialog)
{
    ui->setupUi(this);

    /*
    capWebCam.open(0);

    if(capWebCam.isOpened() == false){
        //ui->textEdit->setText("Error: Could not access cam");
        return;
    }

    //Choose what set of haar features to use for classification
    //faceClassifier.load("C://LibrariesQt//OpenCV//data//haarcascades//haarcascade_frontalface_default.xml");
    //eyeClassifier.load("C://LibrariesQt//OpenCV//data//haarcascades//haarcascade_eye.xml");
    //mouthClassifier.load("C://LibrariesQt//OpenCV//data//haarcascades//haarcascade_frontalface_default.xml");

    /*
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));
    timer->start(20);
    */
}

CamFaceAndEyeDetectionDialog::~CamFaceAndEyeDetectionDialog()
{
    delete ui;
}

void CamFaceAndEyeDetectionDialog::processFrameAndUpdateGUI(){
    /*
    capWebCam.read(matOriginal);

    if (matOriginal.empty()) return;

    // If there is an image to process, do it
    cv::cvtColor(matOriginal, matProcessed, CV_BGR2GRAY);
    cv::flip(matProcessed, matProcessed, 1);
    cv::equalizeHist(matProcessed, matProcessed);

    /*
    faceClassifier.detectMultiScale(matProcessed, faceVec, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(30,30));

    for (faceItr = faceVec.begin() ; faceItr != faceVec.end() ; faceItr++){
        cv::rectangle(matProcessed, *faceItr, cv::Scalar(0, 255, 0));
    }




    if(matProcessed.channels() == 1){
        qImgProcessed = QImage((uchar*)matProcessed.data, matProcessed.cols, matProcessed.rows, matProcessed.step, QImage::Format_Indexed8);
    } else {
        cv::cvtColor(matProcessed, matProcessed, CV_BGR2RGB);
        qImgProcessed = QImage((uchar*)matProcessed.data, matProcessed.cols, matProcessed.rows, matProcessed.step, QImage::Format_RGB888);
    }

    ui->lblCamOutput->setPixmap(QPixmap::fromImage(qImgProcessed));
    */
}

