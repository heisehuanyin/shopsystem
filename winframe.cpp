#include "winframe.h"

#include <QVBoxLayout>

WinFrame::WinFrame(QWidget *parent)
    : QWidget(parent),
      split_base_pane(new QTabWidget(this))
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(split_base_pane);

    split_base_pane->addTab(new QWidget(this), "购物结算");
    split_base_pane->addTab(new QWidget(this), "商品管理");
    split_base_pane->addTab(new QWidget(this), "系统设置");

    showFullScreen();
}

WinFrame::~WinFrame()
{

}
