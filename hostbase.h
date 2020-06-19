#ifndef MGRHOST_H
#define MGRHOST_H

#include "itemdetail.h"

#include <QObject>
#include <QSqlDatabase>

namespace DataModel {
    class HostBase : public QObject
    {
        Q_OBJECT
    public:
        HostBase();
        virtual ~HostBase() = default;

        const QList<ItemDetail>& resultPresent() const
        {
            return results_store;
        }


        void queryByBarcode(const QString &code){}
        void queryByItemname(const QString &name){}

        void commitItemImport(const ItemDetail &item){}

    private:
        QList<ItemDetail> results_store;
        QSqlDatabase dbins;
    };

}
#endif // MGRHOST_H
