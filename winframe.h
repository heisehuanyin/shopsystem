#ifndef WINFRAME_H
#define WINFRAME_H

#include <QCalendarWidget>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QStackedLayout>
#include <QTabWidget>
#include <QTextEdit>
#include <QWidget>

#include "hostbase.h"
#include "picswidget.h"

class WinFrame : public QWidget
{
    Q_OBJECT

public:
    WinFrame(DataModel::HostBase *hostBase, QWidget *parent = nullptr);
    ~WinFrame();

private:
    QTabWidget *const split_base_pane;
    DataModel::HostBase *const host_ins;

    // 库存添加面板
    QComboBox *const query_type;
    QLineEdit *const query_input;
    QStackedLayout *const stack_layout;
    QLineEdit *const item_name_enter;               // 商品名
    QDoubleSpinBox *const item_import_price;        // 进价
    QSpinBox *const item_import_count;              // 入库数量
    QComboBox *const item_import_typeenter;         // 入库单位
    QSpinBox *const item_setmember_count;           // 每套数量
    QDoubleSpinBox *const item_export_single_price; // 零售价
    QDoubleSpinBox *const item_export_set_price;    // 套装售价
    QSpinBox *const valid_deadline_input;           // 有效期限输入
    QComboBox *const valid_deadline_typeenter;      // 有效期单位选择
    QCalendarWidget *const manufacture_date_input;
    QSpinBox *const alarm_before_timeremains;        // 到期提醒倒计时
    QSpinBox *const alarm_before_singleremains;      // 售罄提醒基准点
    QSpinBox *const alarm_before_seteremains;        // 售罄提醒基准点
    QTextEdit *const item_suppliers_present;
    Components::PicsWidget *const capture_widget;
    QLabel *const item_imagedisplay;
    QPushButton *const commit_edit, *const change_pic, *const cancel_edit;

    QWidget *build_import_pane(QWidget *paneBase);
    void item_import_query(const QString &text);
    void _load_current_import_item_details();
    void _commit_items_import();
};

#endif // WINFRAME_H
