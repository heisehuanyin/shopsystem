#ifndef PICSWIDGET_H
#define PICSWIDGET_H

#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QWidget>

namespace Components {
    class PicsWidget : public QWidget
    {
        Q_OBJECT

    public:
        PicsWidget(QWidget *parent=nullptr);
        virtual ~PicsWidget() override = default;

        void openCapture();

    private:
        QCameraViewfinder *const viewfinder;
        QCamera *const camera_ins;
        QCameraImageCapture *capture_foundation;

    signals:
        void captureReady(int id, const QImage &ins);
    };
}

#endif // PICSWIDGET_H
