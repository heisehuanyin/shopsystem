#ifndef ITEMDETAIL_H
#define ITEMDETAIL_H

#include "common.h"
#include <QDate>
#include <QPair>

namespace DataModel {
    class ItemDetail
    {
    public:
        ItemDetail(QString idSeriescode);
        ItemDetail(const ItemDetail &other);
        virtual ~ItemDetail();

        QString idSeriescode() const;

        QString name() const;
        void resetName(const QString &name);

        qreal importPrice() const;
        void resetImportPrice(qreal price);

        enum importType{ Single, Set };
        int ImportCount() const;
        importType importType() const;
        void resetImportCount(int count, enum importType type);

        qreal exportSinglePrice() const;
        void resetExportSinglePrice(qreal price);

        int setMembersCount() const;
        void resetSetMembersCount(int count);

        qreal exportSetPrice() const;
        void resetExportSetPrice(qreal price);

        QDate manufactureDate() const;
        void resetManufactureDate(const QDate &date);

        enum timeSpanType { Days, Month };
        int validTimespan() const;
        timeSpanType validTimespanType() const;
        void resetValidtimeSpan(int timespan, timeSpanType type);

        int alarmDaysBeforeInvalid() const;
        void resetAlarmDaysBeforeInvalid(int days);

        int alarmAtSingleLeastCount() const;
        int alarmAtSetLeastCount() const;
        void resetAlarmAtNumbersCount(int number, enum importType type);

        QString imageUrl() const;
        void resetImageUrl(const QString &url);

        QString supplierRecords() const;
        void resetSupplierRecords(const QString &records_string);
    private:
        const QString id_seriescode_store;
        QString item_name_store;
        QString item_image_url;
        qreal item_import_price;
        int item_import_count;
        enum importType item_import_type_store;
        QString records_string;
        qreal item_sell_singleprice;
        int membercount_under_set;
        qreal item_sell_setprice;
        QDate manufacture_date;
        int valid_timespan_store;
        enum timeSpanType valid_timespan_type;
        int alram_days_before_invalid;
        int alarm_at_single_least;
        int alarm_at_set_least;
    };
}

#endif // ITEMDETAIL_H


































