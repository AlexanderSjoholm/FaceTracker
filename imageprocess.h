#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include "thresholddialog.h"

class ImageProcess
{
public:
    ImageProcess();

    static void grayScale(cv::Mat &input, cv::Mat &output);
    static void threshold(cv::Mat &input, cv::Mat &output);
};

#endif // IMAGEPROCESS_H
