#ifndef WEBCAMDIALOG_H
#define WEBCAMDIALOG_H

#include <QDialog>
#include <opencv2/features2d/features2d.hpp>
#include "imageprocess.h"

namespace Ui {
class WebCamDialog;
}

class WebCamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WebCamDialog(QWidget *parent = 0);
    ~WebCamDialog();

private slots:
    void processFrameAndGUI();

private:
    Ui::WebCamDialog *ui;

    cv::VideoCapture capWebCam;

    cv::Mat matOriginal;
    cv::Mat matProcessed;

    QImage qImgOriginal;
    QImage qImgProcessed;

    std::vector<cv::Vec3f> vecCircles;
    std::vector<cv::Vec3f>::iterator itrCircles;

    QTimer* camTimer;
};

#endif // WEBCAMDIALOG_H
