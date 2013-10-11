#ifndef THRESHOLDDIALOG_H
#define THRESHOLDDIALOG_H

#include <QDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "mainwindow.h"

namespace Ui {
class ThresholdDialog;
}

class ThresholdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThresholdDialog(QWidget *parent = 0);

    void init(cv::Mat &input, cv::Mat *output);

    cv::Mat input, *output, preview;
    int thresholdValue, maxBinaryValue, type;

    ~ThresholdDialog();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_horizontalSlider_valueChanged(int value);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_buttonBox_destroyed();

private:
    Ui::ThresholdDialog *ui;
};

#endif // THRESHOLDDIALOG_H
