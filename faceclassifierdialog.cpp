#include "faceclassifierdialog.h"
#include "ui_faceclassifierdialog.h"

FaceClassifierDialog::FaceClassifierDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FaceClassifierDialog)
{
    ui->setupUi(this);

    // Open cam and see if it works
    capWebCam.open(0);
    if(capWebCam.isOpened() == false) return;

    // Read glasses image
    matGlassesGray = cv::imread("D://Dev//Qt//OpenCV//GUIApp//deal_with_it_glasses_white.png", 0);
    cv::cvtColor(matGlassesGray, matGlassesRGB, CV_GRAY2RGB);
    //cv::split(matGlasses, RGBASplit);

    draw = false;

    // Choose what set of haar features to use for classification
    faceClassifier.load("C://LibrariesQt//OpenCV//data//haarcascades//haarcascade_frontalface_default.xml");
    eyeClassifier.load("C://LibrariesQt//OpenCV//data//haarcascades//haarcascade_mcs_eyepair_big.xml");
    mouthClassifier.load("C://LibrariesQt//OpenCV//data//haarcascades//haarcascade_mcs_mouth.xml");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGUI()));
    timer->start(20);
}

FaceClassifierDialog::~FaceClassifierDialog()
{
    delete ui;
}

void FaceClassifierDialog::updateGUI(){
    // Grab frame from cam and see if it works
    capWebCam.read(matOriginal);
    if (matOriginal.empty()) return;

    // Process image
    cv::cvtColor(matOriginal, matProcessed, CV_BGR2GRAY);
    cv::flip(matProcessed, matProcessed, 1);
    cv::equalizeHist(matProcessed, matProcessed);

    // Classify
    faceClassifier.detectMultiScale(matProcessed, faceVec, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(30,30));

    faceFound = false;

    if (faceVec.empty() == false){
        matFace = matProcessed(*(faceVec.begin()));
        cv::cvtColor(matFace, matFace, CV_GRAY2RGB);
    }

    //eyeClassifier.detectMultiScale(matFace, eyeVec, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(5, 5), cv::Size(50, 50));

    // Convert color to get colored rectangles
    cv::cvtColor(matProcessed, matProcessed, CV_GRAY2RGB);

    // Draw classified objects
    for (faceItr = faceVec.begin() ; faceItr != faceVec.end() ; faceItr++){

        matFace = matProcessed(*faceItr);

        //cv::rectangle(matProcessed, *faceItr, cv::Scalar(0, 255, 0));

        eyeClassifier.detectMultiScale(matFace, eyeVec, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(5, 5), cv::Size(50, 50));

        for (eyeItr = eyeVec.begin() ; eyeItr != eyeVec.end() ; eyeItr++){
            //cv::GaussianBlur(matFace(*eyeItr), matFace(*eyeItr), cv::Size(9,9), 5);
            //cv::Canny(matFace(*eyeItr), matFace(*eyeItr), 10, 100);
            if (eyeVec.empty() == false){
                matEyes = matFace(*eyeItr);
                eyePos = cv::Point2i((*eyeItr).x, (*eyeItr).y);
                //cv::rectangle(matFace, *eyeItr, cv::Scalar(0, 255, 0));
                faceFound = true;
            }
        }
    }

    // Put on your glasses
    // The glasses are 700 px wide 260 px in from left border 50 px down from top
    if (draw && faceFound) {
        //ui->textEdit->append(QString("Cols") + QString::number(matEyes.cols));
        //ui->textEdit->append(QString("Rows") + QString::number(matGlassesRGB.rows));
        scale = (float) matEyes.cols / 600;

        if (scale > 0){
            cv::resize(matGlassesGray, matGlasses, cv::Size(0,0), scale, scale, CV_INTER_LINEAR);

            int numberOfRows = matGlasses.rows;
            int numberOfCols = matGlasses.cols;

            int xOffset = -50*scale;
            int yOffset = -350*scale;

            for (int i = 0; i < numberOfRows; i++){
                for (int j = 0; j < numberOfCols; j++){
                    if (matGlasses.at<uchar>(i,j) != 0){
                        matEyes.at<cv::Vec3b>(i + xOffset,j + yOffset)[0] = 0;
                        matEyes.at<cv::Vec3b>(i + xOffset,j + yOffset)[1] = 0;
                        matEyes.at<cv::Vec3b>(i + xOffset,j + yOffset)[2] = 0;
                    }
                }
            }
            //matFace(matGlasses.row, matGlasses.colRange).setTo(0, matGlasses);
        }
    }

    // Display image
    //cv::cvtColor(matProcessed, matProcessed, CV_GRAY2RGB);
    qImgProcessed = QImage((uchar*)matProcessed.data, matProcessed.cols, matProcessed.rows, matProcessed.step, QImage::Format_RGB888);
    ui->imageLbl->setPixmap(QPixmap::fromImage(qImgProcessed));

    // Display face
    scale = (float) ui->faceLbl->height() / matFace.rows;
    cv::resize(matFace, matFace, cv::Size(0,0), scale, scale, CV_INTER_NN);

    qImgFace = QImage((uchar*)matFace.data, matFace.cols, matFace.rows, matFace.step, QImage::Format_RGB888);
    ui->faceLbl->setPixmap(QPixmap::fromImage(qImgFace));

    // Display eyes
    scale = (float) ui->eyeLbl->width() / matEyes.cols;
    cv::resize(matEyes, matEyes, cv::Size(0,0), scale, scale, CV_INTER_NN);

    qImgEyes = QImage((uchar*)matEyes.data, matEyes.cols, matEyes.rows, matEyes.step, QImage::Format_RGB888);
    ui->eyeLbl->setPixmap(QPixmap::fromImage(qImgEyes));

    // Display glasses
    scale = (float) ui->glassesLbl->width() / matGlassesRGB.cols;
    cv::resize(matGlassesRGB, matGlassesRGB, cv::Size(0,0), scale, scale, CV_INTER_NN);

    qImgGlasses = QImage((uchar*)matGlassesRGB.data, matGlassesRGB.cols, matGlassesRGB.rows, matGlassesRGB.step, QImage::Format_RGB888);
    //ui->glassesLbl->setPixmap(QPixmap::fromImage(qImgGlasses));

}

void FaceClassifierDialog::on_radioButtonDraw_clicked(bool checked){
    if (checked){
        draw = true;
        ui->glassesLbl->setPixmap(QPixmap::fromImage(qImgGlasses));
        ui->textEdit->append(QString("Deal with it"));
    } else {
        draw = false;
    }
}
