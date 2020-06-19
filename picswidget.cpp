#include "picswidget.h"

#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QPushButton>
#include <QVBoxLayout>

using namespace Components;

PicsWidget::PicsWidget(QWidget *parent)
    :QWidget(parent),
      viewfinder(new QCameraViewfinder(this)),
      camera_ins(new QCamera(this)),
      capture_foundation(new QCameraImageCapture(camera_ins, this))
{
    camera_ins->setViewfinder(viewfinder);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(viewfinder);
    auto pic_capture = new QPushButton("拍摄照片", this);
    layout->addWidget(pic_capture);

    connect(pic_capture,    &QPushButton::clicked,  [=](){
        capture_foundation->capture();
        camera_ins->unlock();
    });
    connect(capture_foundation, &QCameraImageCapture::imageCaptured,  [=](int id, const QImage &ins){
        emit this->captureReady(id, ins);
        camera_ins->stop();
    });
}

void PicsWidget::openCapture()
{
    camera_ins->setCaptureMode(QCamera::CaptureStillImage);

    camera_ins->start();
    camera_ins->searchAndLock();
}
