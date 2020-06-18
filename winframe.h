#ifndef WINFRAME_H
#define WINFRAME_H

#include <QTabWidget>
#include <QWidget>

class WinFrame : public QWidget
{
    Q_OBJECT

public:
    WinFrame(QWidget *parent = nullptr);
    ~WinFrame();

private:
    QTabWidget *const split_base_pane;

};

#endif // WINFRAME_H
