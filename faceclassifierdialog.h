#ifndef FACECLASSIFIERDIALOG_H
#define FACECLASSIFIERDIALOG_H

#include <QDialog>
#include "imageprocess.h"

namespace Ui {
class FaceClassifierDialog;
}

class FaceClassifierDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FaceClassifierDialog(QWidget *parent = 0);
    ~FaceClassifierDialog();

private slots:
    void updateGUI();

    void on_radioButtonDraw_clicked(bool checked);

private:
    Ui::FaceClassifierDialog *ui;

    cv::VideoCapture capWebCam;

    cv::CascadeClassifier faceClassifier, eyeClassifier, mouthClassifier;

    std::vector<cv::Rect> faceVec, eyeVec, mouthVec;
    std::vector<cv::Rect>::iterator faceItr, eyeItr, mouthItr;

    std::vector<cv::Mat> RGBASplit;
    float scale;
    cv::Point2i eyePos;
    bool draw, faceFound;

    cv::Mat matOriginal, matProcessed, matFace, matEyes, matEyeLeft, matEyeRight, matGlassesGray, matGlassesRGB, matGlasses;
    QImage qImgOriginal, qImgProcessed, qImgFace, qImgEyes, qImgEyeLeft, qImgEyeRight, qImgGlasses;


    QTimer* timer;
};

#endif // FACECLASSIFIERDIALOG_H
