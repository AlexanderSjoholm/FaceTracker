#include "webcamdialog.h"
#include "ui_webcamdialog.h"

WebCamDialog::WebCamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WebCamDialog)
{
    ui->setupUi(this);

    capWebCam.open(0);

    if(capWebCam.isOpened() == false){
        ui->textEdit->setText("Error: Could not access cam");
        return;
    }

    camTimer = new QTimer(this);
    connect(camTimer, SIGNAL(timeout()), this, SLOT(processFrameAndGUI()));
    camTimer->start(20);
}

WebCamDialog::~WebCamDialog()
{
    delete ui;
}

void WebCamDialog::processFrameAndGUI(){
    capWebCam.read(matOriginal);

    if(matOriginal.empty()) return;

    cv::flip(matOriginal, matProcessed, 1);
    //matProcessed = matOriginal;
    // Välj vilken färg som skall fokuseras
    //cv::inRange(matProcessed, cv::Scalar(0, 0, 128), cv::Scalar(64, 64, 256), matProcessed);
    //cv::threshold(matProcessed, matProcessed, 128, 1, 3);
    cv::GaussianBlur(matProcessed, matProcessed, cv::Size(9,9), 2);

    cv::Canny(matProcessed, matProcessed, 10, 100);

    //std::vector<cv::Point2f> features;
    //cv::goodFeaturesToTrack(matProcessed, features, 5, 0.2, 0.5);





    //cv::cvtColor(matProcessed, matProcessed, CV_BGR2GRAY);
    //cv::threshold(matProcessed, matProcessed, 128, 255, 0);
    /*
    cv::HoughCircles(matProcessed, vecCircles, CV_HOUGH_GRADIENT, 2, matProcessed.rows/4, 100, 50, 10, 400);

    for(itrCircles = vecCircles.begin(); itrCircles != vecCircles.end(); itrCircles++){
        ui->textEdit->append(QString("Ball Position x = ") + QString::number((*itrCircles)[0]) +
                             QString("Ball Position y = ") + QString::number((*itrCircles)[1]) +
                             QString("Ball Radius = ") +     QString::number((*itrCircles)[2], 'f', 3 ));

        cv::flip(matOriginal, matOriginal, 1);
        cv::circle(matOriginal, cv::Point((int)(*itrCircles)[0], (int)(*itrCircles)[1]), (*itrCircles)[2], cv::Scalar(0, 255, 0), 3);
    }
    */

    //cv::imshow("CamOriginal", matOriginal);
    //cv::imshow("CamProcessed", matProcessed);

    cv::cvtColor(matOriginal, matOriginal, CV_BGR2RGB);
    qImgOriginal = QImage((uchar*)matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_RGB888);

    if(matProcessed.channels() == 1){
        qImgProcessed = QImage((uchar*)matProcessed.data, matProcessed.cols, matProcessed.rows, matProcessed.step, QImage::Format_Indexed8);
    } else {
        cv::cvtColor(matProcessed, matProcessed, CV_BGR2RGB);
        qImgProcessed = QImage((uchar*)matProcessed.data, matProcessed.cols, matProcessed.rows, matProcessed.step, QImage::Format_RGB888);
    }


    ui->lblOriginalImage->setPixmap(QPixmap::fromImage(qImgOriginal));
    ui->lblProcessedImage->setPixmap(QPixmap::fromImage(qImgProcessed));

}
