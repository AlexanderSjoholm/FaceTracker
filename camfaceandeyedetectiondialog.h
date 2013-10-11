#ifndef CAMFACEANDEYEDETECTIONDIALOG_H
#define CAMFACEANDEYEDETECTIONDIALOG_H

#include <QDialog>
#include "imageprocess.h"

namespace Ui {
class CamFaceAndEyeDetectionDialog;
}

class CamFaceAndEyeDetectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CamFaceAndEyeDetectionDialog(QWidget *parent = 0);
    ~CamFaceAndEyeDetectionDialog();

private slots:
    void processFrameAndUpdateGUI();

private:
    Ui::CamFaceAndEyeDetectionDialog *ui;

    cv::VideoCapture capWebCam;
    /*
    cv::CascadeClassifier faceClassifier, eyeClassifier, mouthClassifier;

    std::vector<cv::Rect> faceVec, eyeVec, mouthVec;
    std::vector<cv::Rect>::iterator faceItr, eyeItr, mouthItr;

    QTimer* timer;
    */

    cv::Mat matOriginal;
    cv::Mat matProcessed;

    QImage qImgOriginal;
    QImage qImgProcessed;
};

#endif // CAMFACEANDEYEDETECTIONDIALOG_H
