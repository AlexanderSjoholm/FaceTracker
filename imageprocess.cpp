#include "imageprocess.h"

ImageProcess::ImageProcess()
{
}

void ImageProcess::grayScale(cv::Mat &input, cv::Mat &output)
{
    if(input.channels() == 3){
        cv::cvtColor(input, output, CV_BGR2GRAY);
    }
}

void ImageProcess::threshold(cv::Mat &input, cv::Mat &output){
    ThresholdDialog thresholdDialog;
    thresholdDialog.init(input, &output);
    thresholdDialog.exec();
}
