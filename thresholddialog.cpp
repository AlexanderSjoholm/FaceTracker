#include "thresholddialog.h"
#include "ui_thresholddialog.h"

ThresholdDialog::ThresholdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThresholdDialog)
{
    ui->setupUi(this);

    thresholdValue = 128;
    maxBinaryValue = 255;
    type = 0;

    ui->comboBox->addItem("Binary");
    ui->comboBox->addItem("Binary Inverted");
    ui->comboBox->addItem("Threshold Truncated");
    ui->comboBox->addItem("Threshold to Zero");
    ui->comboBox->addItem("Threshold to Zero Inverted");
    ui->comboBox->adjustSize();
}

ThresholdDialog::~ThresholdDialog()
{
    delete ui;
}

void ThresholdDialog::init(cv::Mat &_input, cv::Mat *_output){
    input = _input;
    output = _output;
    preview = _input.clone();

    cv::threshold(input, preview, thresholdValue, maxBinaryValue, type);
    cv::namedWindow("Preview");
    cv::imshow("Preview", preview);
}

void ThresholdDialog::on_comboBox_currentIndexChanged(int index){
    type = index;
    if(!input.empty()){
        cv::threshold(input, preview, thresholdValue, maxBinaryValue, type);
        cv::imshow("Preview", preview);
    }
}

void ThresholdDialog::on_horizontalSlider_valueChanged(int value){
    thresholdValue = value;
    cv::threshold(input, preview, thresholdValue, maxBinaryValue, type);
    cv::imshow("Preview", preview);
}

void ThresholdDialog::on_buttonBox_accepted(){
    *output = preview.clone();
    cv::destroyWindow("Preview");
}

void ThresholdDialog::on_buttonBox_rejected(){
    cv::destroyWindow("Preview");
}

void ThresholdDialog::on_buttonBox_destroyed(){
    cv::destroyWindow("Preview");
}
