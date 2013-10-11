#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    cv::Mat image[10], preview;
    QVector<cv::Mat> history[10];
    int imageCounter, activeImage;

private slots:
    void on_actionOpen_triggered();
    void display();
    void on_actionFlip_X_triggered();
    void on_actionFlip_Y_triggered();
    void on_actionGray_Scale_triggered();
    void on_actionUndo_triggered();
    void on_actionThreshold_triggered();
    void on_actionOpen_recent_triggered();
    void on_actionOpen_Web_Cam_triggered();

    void processFrameAndUpdateGUI();

    void on_actionFace_Eye_Detection_triggered();

private:
    Ui::MainWindow *ui;
    QTimer* mainTimer;
};

#endif // MAINWINDOW_H
