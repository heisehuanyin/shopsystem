#include "itemdetail.h"
#include "itemdetail.h"

using namespace DataModel;

ItemDetail::ItemDetail(QString idNumber)
    :id_seriescode_store(idNumber),
      item_name_store("未知商品"),
      item_image_url(":/image/items/package.jpeg"),
      item_import_price(0.0),
      item_import_count(1),
      item_import_type_store(importType::Single),
      records_string(""),
      item_sell_singleprice(0.0),
      membercount_under_set(0),
      item_sell_setprice(0.0),
      manufacture_date(QDate::currentDate()),
      valid_timespan_store(0),
      valid_timespan_type(timeSpanType::Days),
      alram_days_before_invalid(0),
      alarm_at_single_least(1),
      alarm_at_set_least(1){}

ItemDetail::ItemDetail(const ItemDetail &other)
    :id_seriescode_store(other.id_seriescode_store),
      item_name_store(other.item_name_store),
      item_image_url(other.item_image_url),
      item_import_price(other.item_import_price),
      item_import_count(other.item_import_count),
      item_import_type_store(other.item_import_type_store),
      records_string(other.records_string),
      item_sell_singleprice(other.item_sell_singleprice),
      membercount_under_set(other.membercount_under_set),
      item_sell_setprice(other.item_sell_setprice),
      manufacture_date(other.manufacture_date),
      valid_timespan_store(other.valid_timespan_store),
      valid_timespan_type(other.valid_timespan_type),
      alram_days_before_invalid(other.alram_days_before_invalid),
      alarm_at_single_least(other.alarm_at_single_least),
      alarm_at_set_least(other.alarm_at_set_least){}

ItemDetail::~ItemDetail(){}

QString ItemDetail::idSeriescode() const
{
    return id_seriescode_store;
}

QString ItemDetail::name() const
{
    return item_name_store;
}

void ItemDetail::resetName(const QString &name)
{
    item_name_store = name;
}

qreal ItemDetail::importPrice() const
{
    return item_import_price;
}

void ItemDetail::resetImportPrice(qreal price)
{
    item_import_price = price;
}

int ItemDetail::ImportCount() const
{
    return item_import_count;
}

enum ItemDetail::importType ItemDetail::importType() const
{
    return item_import_type_store;
}

void ItemDetail::resetImportCount(int count, enum ItemDetail::importType type)
{
    item_import_count = count;
    item_import_type_store = type;
}

qreal ItemDetail::exportSinglePrice() const
{
    return item_sell_singleprice;
}

void ItemDetail::resetExportSinglePrice(qreal price)
{
    item_sell_singleprice = price;
}

int ItemDetail::setMembersCount() const
{
    return membercount_under_set;
}

void ItemDetail::resetSetMembersCount(int count)
{
    membercount_under_set = count;
}

qreal ItemDetail::exportSetPrice() const
{
    return item_sell_setprice;
}

void ItemDetail::resetExportSetPrice(qreal price)
{
    item_sell_setprice = price;
}

QDate ItemDetail::manufactureDate() const
{
    return manufacture_date;
}

void ItemDetail::resetManufactureDate(const QDate &date)
{
    manufacture_date = date;
}

int ItemDetail::validTimespan() const
{
    return valid_timespan_store;
}

ItemDetail::timeSpanType ItemDetail::validTimespanType() const
{
    return valid_timespan_type;
}

void ItemDetail::resetValidtimeSpan(int timespan, ItemDetail::timeSpanType type)
{
    timespan = valid_timespan_store;
    valid_timespan_type = type;
}

int ItemDetail::alarmDaysBeforeInvalid() const
{
    return alram_days_before_invalid;
}

void ItemDetail::resetAlarmDaysBeforeInvalid(int days)
{
    alram_days_before_invalid = days;
}

int ItemDetail::alarmAtSingleLeastCount() const
{
    return alarm_at_single_least;
}

int ItemDetail::alarmAtSetLeastCount() const
{
    return alarm_at_set_least;
}

void ItemDetail::resetAlarmAtNumbersCount(int number, enum ItemDetail::importType type)
{
    switch (type) {
        case importType::Single:
            alarm_at_single_least = number;
            break;
        case importType::Set:
            alarm_at_set_least = number;
            break;
    }
}

QString ItemDetail::imageUrl() const
{
    return item_image_url;
}

void ItemDetail::resetImageUrl(const QString &url)
{
    item_image_url = url;
}

QString ItemDetail::supplierRecords() const
{
    return records_string;
}

void ItemDetail::resetSupplierRecords(const QString &records_string)
{
    this->records_string = records_string;
}

