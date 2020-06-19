#include "winframe.h"

#include <QCamera>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QStackedLayout>
#include <QVBoxLayout>

using namespace DataModel;
using namespace Components;

WinFrame::WinFrame(DataModel::HostBase *hostBase, QWidget *parent)
    : QWidget(parent),
      split_base_pane(new QTabWidget(this)),
      host_ins(hostBase),
      // 库存添加面板
      query_type(new QComboBox(this)),
      query_input(new QLineEdit(this)),
      stack_layout(new QStackedLayout()),
      item_name_enter(new QLineEdit(this)),              // 商品名
      item_import_price(new QDoubleSpinBox(this)),       // 进价
      item_import_count(new QSpinBox(this)),             // 入库数量
      item_import_typeenter(new QComboBox(this)),                  // 入库单位
      item_setmember_count(new QSpinBox(this)),          // 每套数量
      item_export_single_price(new QDoubleSpinBox(this)),// 零售价
      item_export_set_price(new QDoubleSpinBox(this)),   // 套装售价
      valid_deadline_input(new QSpinBox(this)),          // 有效期限输入
      valid_deadline_typeenter(new QComboBox(this)),     // 有效期单位选择
      manufacture_date_input(new QCalendarWidget(this)),
      alarm_before_timeremains(new QSpinBox(this)),      // 到期提醒倒计时
      alarm_before_singleremains(new QSpinBox(this)),    // 售罄提醒基准点
      alarm_before_seteremains(new QSpinBox(this)),      // 基准点单位
      item_suppliers_present(new QTextEdit(this)),
      capture_widget(new PicsWidget(this)),
      item_imagedisplay(new QLabel(this)),
      commit_edit(new QPushButton("提交修改", this)),
      change_pic(new QPushButton("更新照片", this)),
      cancel_edit(new QPushButton("取消入库", this))
{
    auto layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);
    split_base_pane->setTabPosition(QTabWidget::East);
    split_base_pane->setStyleSheet("QTabBar::tab {height:160px;width:40px;font: 28px;}");
    layout->addWidget(split_base_pane);

    split_base_pane->addTab(new QWidget(this), "购物结算");
    split_base_pane->addTab(build_import_pane(this), "进货录入");
    split_base_pane->addTab(new QWidget(this), "库存统计");
    split_base_pane->addTab(new QWidget(this), "销售记录");
    split_base_pane->addTab(new QWidget(this), "系统设置");


    //showFullScreen();
}

WinFrame::~WinFrame()
{

}

QWidget* WinFrame::build_import_pane(QWidget *paneBase)
{
    auto panel(new QWidget(paneBase));
    auto grid_layout(new QGridLayout(panel));

    grid_layout->addWidget(query_type);

    grid_layout->addWidget(query_input, 0, 1, 1, 4);
    connect(query_input,    &QLineEdit::textChanged,    this,   &WinFrame::item_import_query);
    query_type->addItems(QStringList() << "条形码" << "商品名称");
    connect(query_type, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int){
        query_input->clear();
    });

    auto bottom_area(new QWidget(panel));
    grid_layout->addWidget(bottom_area, 1, 0, 5, 5);
    bottom_area->setLayout(stack_layout);
    // 空白面板
    {
        auto empty_panel(new QWidget(bottom_area));
        stack_layout->addWidget(empty_panel);
    }
    // 商品详细面板
    {
        auto information_modify = new QWidget(bottom_area);
        stack_layout->addWidget(information_modify);

        // 构建面板:左部输入区
        auto information_layout = new QGridLayout(information_modify);
        information_layout->addWidget(new QLabel("商品名称：", this), 0, 0);
        information_layout->addWidget(this->item_name_enter, 0, 1, 1, 2);
        information_layout->addWidget(new QLabel("商品进价：", this), 1, 0);
        information_layout->addWidget(this->item_import_price, 1, 1, 1, 2);
        information_layout->addWidget(new QLabel("入库数量：", this), 2, 0);
        information_layout->addWidget(this->item_import_count, 2, 1, 1, 2);
        information_layout->addWidget(new QLabel("入库单位：", this), 3, 0);
        information_layout->addWidget(this->item_import_typeenter, 3, 1, 1, 2);
        information_layout->addWidget(new QLabel("每套组成：", this), 4, 0);
        information_layout->addWidget(this->item_setmember_count, 4, 1, 1, 2);
        information_layout->addWidget(new QLabel("零售价：", this), 5, 0);
        information_layout->addWidget(this->item_export_single_price, 5, 1, 1, 2);
        information_layout->addWidget(new QLabel("套装售价：", this), 6, 0);
        information_layout->addWidget(this->item_export_set_price, 6, 1, 1, 2);
        information_layout->addWidget(new QLabel("有效期长度：", this), 7, 0);
        information_layout->addWidget(this->valid_deadline_input, 7, 1, 1, 2);
        information_layout->addWidget(new QLabel("有效期单位：", this), 8, 0);
        information_layout->addWidget(this->valid_deadline_typeenter, 8, 1, 1, 2);
        auto group = new QGroupBox("生产日期输入：", this);
        (new QVBoxLayout(group))->addWidget(manufacture_date_input);
        information_layout->addWidget(group, 9, 0, 3, 3);
        information_layout->addWidget(new QLabel("失效前提示时间：", this), 12, 0);
        information_layout->addWidget(this->alarm_before_timeremains, 12, 1, 1, 2);
        information_layout->addWidget(new QLabel("数量不足提示：", this), 13, 0);
        information_layout->addWidget(this->alarm_before_singleremains, 13, 1, 1, 2);
        information_layout->addWidget(new QLabel("套装不足提示：", this), 14, 0);
        information_layout->addWidget(this->alarm_before_seteremains, 14, 1, 1, 2);
        information_layout->addWidget(this->item_suppliers_present, 15, 0, 3, 3);
        // 构架面板：右部显示区域
        auto display_union(new QWidget(this));
        auto display_stack = new QStackedLayout(display_union);
        information_layout->addWidget(display_union, 0, 3, 17, 6);

        auto item_presentarea(new QScrollArea(this));
        item_imagedisplay->setPixmap(QPixmap(":/image/items/package.jpeg"));
        item_presentarea->setWidget(item_imagedisplay);
        auto vboxlayout(new QVBoxLayout(new QWidget(this)));
        vboxlayout->addWidget(item_presentarea);
        vboxlayout->addWidget(change_pic);
        display_stack->addWidget(vboxlayout->parentWidget());       // 显示widget
        connect(change_pic, &QPushButton::clicked,  [=](){
            capture_widget->openCapture();
            display_stack->setCurrentIndex(1);
        });
        display_stack->addWidget(capture_widget);                   // 摄制widget
        connect(capture_widget, &PicsWidget::captureReady,  [=](int, const QImage &ins){
            item_imagedisplay->setPixmap(QPixmap::fromImage(ins));
            display_stack->setCurrentIndex(0);
            item_imagedisplay->show();
        });


        information_layout->addWidget(cancel_edit, 17, 7);
        information_layout->addWidget(commit_edit, 17, 8);

        // 配置页面
        item_import_price->setValue(0.0);
        item_import_price->setPrefix("￥：");
        item_import_count->setValue(1);
        item_import_count->setPrefix("个(只、根)：");
        item_import_typeenter->addItems(QStringList() << "单个" << "套组");
        item_setmember_count->setValue(0);
        item_export_single_price->setValue(0.0);
        item_export_single_price->setPrefix("￥：");
        item_export_set_price->setValue(0.0);
        item_export_set_price->setPrefix("￥：");
        valid_deadline_input->setValue(10);
        valid_deadline_input->setPrefix("天：");
        valid_deadline_typeenter->addItems(QStringList() << "天" << "月");
        alarm_before_timeremains->setValue(10);
        alarm_before_timeremains->setPrefix("天：");
        alarm_before_singleremains->setValue(1);
        alarm_before_singleremains->setPrefix("个(只、根)：");
        alarm_before_seteremains->setPrefix("套(组、打)：");

        connect(item_import_typeenter,    QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index){
            switch (index) {
                case 0:
                    item_import_count->setPrefix("个(只、根)：");
                    break;
                case 1:
                    item_import_count->setPrefix("套(组、打)：");
                    break;
            }
        });
        connect(valid_deadline_typeenter, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index){
            switch (index) {
                case 0:
                    valid_deadline_input->setPrefix("天：");
                    break;
                case 1:
                    valid_deadline_input->setPrefix("月：");
                    break;
            }
        });
        connect(cancel_edit,    &QPushButton::clicked,  [=](){query_input->setText("*"); query_input->clear();});
        connect(commit_edit,    &QPushButton::clicked,  this,   &WinFrame::_commit_items_import);

    }
    // 空白响应页面
    {
        auto import_confirm = new QWidget(bottom_area);
        auto layout = new QGridLayout(import_confirm);
        layout->addWidget(new QLabel("<h1>库存检索</h1><h2>库存中没有与指定条形码匹配的商品信息，是否添加新条目？", import_confirm), 0, 0, 1, 2);
        layout->addWidget(new QPushButton("新增库存条目", import_confirm), 1, 0, 1, 1);
        layout->addWidget(new QPushButton("清除输入信息", import_confirm), 1, 1, 1, 1);
        stack_layout->addWidget(import_confirm);
    }

    stack_layout->setCurrentIndex(0);
    return panel;
}

void WinFrame::item_import_query(const QString &text)
{
    if(!text.size()){
        stack_layout->setCurrentIndex(0);
        return;
    }

    switch (query_type->currentIndex()) {
        case 0: // 条形码
            host_ins->queryByBarcode(text);
            break;
        case 1: // 商品名称
            host_ins->queryByItemname(text);
            break;
    }

    if(host_ins->resultPresent().size()){
        stack_layout->setCurrentIndex(1);
        _load_current_import_item_details();
    }
    else {
        if(!query_type->currentIndex()){
            stack_layout->setCurrentIndex(2);
        }
        else {
            stack_layout->setCurrentIndex(0);
        }
    }
}

void WinFrame::_load_current_import_item_details()
{
    auto item_detail = host_ins->resultPresent().at(0);

    item_name_enter->setText(item_detail.name());
    item_import_price->setValue(item_detail.importPrice());
    item_import_count->setValue(item_detail.ImportCount());
    if(item_detail.importType() == ItemDetail::importType::Single){
        item_import_typeenter->setCurrentIndex(0);
    }
    else {
        item_import_typeenter->setCurrentIndex(1);
    }
    item_setmember_count->setValue(item_detail.setMembersCount());
    item_export_single_price->setValue(item_detail.exportSinglePrice());
    item_export_set_price->setValue(item_detail.exportSetPrice());
    valid_deadline_input->setValue(item_detail.validTimespan());
    if(item_detail.validTimespanType() == ItemDetail::timeSpanType::Days){
        valid_deadline_typeenter->setCurrentIndex(0);
    }
    else {
        valid_deadline_typeenter->setCurrentIndex(1);
    }
    manufacture_date_input->setSelectedDate(item_detail.manufactureDate());
    alarm_before_timeremains->setValue(item_detail.alarmDaysBeforeInvalid());
    alarm_before_singleremains->setValue(item_detail.alarmAtSingleLeastCount());
    alarm_before_seteremains->setValue(item_detail.alarmAtSetLeastCount());
    item_suppliers_present->setPlainText(item_detail.supplierRecords());
    item_imagedisplay->setPixmap(QPixmap(item_detail.imageUrl()));
}

void WinFrame::_commit_items_import()
{
    ItemDetail item(query_input->text());

    item.resetName(item_name_enter->text());
    item.resetImportPrice(item_import_price->value());
    switch (item_import_typeenter->currentIndex()) {
        case 0:
            item.resetImportCount(item_import_count->value(), ItemDetail::importType::Single);
            break;
        case 1:
            item.resetImportCount(item_import_count->value(), ItemDetail::importType::Set);
            break;
    }
    item.resetSetMembersCount(item_setmember_count->value());
    item.resetExportSinglePrice(item_export_single_price->value());
    item.resetExportSetPrice(item_export_set_price->value());
    switch (valid_deadline_typeenter->currentIndex()) {
        case 0:     // 天
            item.resetValidtimeSpan(valid_deadline_input->value(), ItemDetail::Days);
            break;
        case 1:     // 月
            item.resetValidtimeSpan(valid_deadline_input->value(), ItemDetail::Month);
            break;
    }
    item.resetManufactureDate(manufacture_date_input->selectedDate());
    item.resetAlarmDaysBeforeInvalid(alarm_before_timeremains->value());
    item.resetAlarmAtNumbersCount(alarm_before_singleremains->value(), ItemDetail::Single);
    item.resetAlarmAtNumbersCount(alarm_before_seteremains->value(), ItemDetail::Set);
    item.resetSupplierRecords(item_suppliers_present->toPlainText());
    item.resetImageUrl(query_input->text()+".jpeg");

    host_ins->commitItemImport(item);
}
