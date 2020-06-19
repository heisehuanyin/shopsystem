#include "hostbase.h"

#include <QSqlQuery>
#include <QSqlError>

using namespace DataModel;

HostBase::HostBase()
{
    dbins = QSqlDatabase::addDatabase("QSQLITE");
    dbins.setDatabaseName("Tables.db");
    if(!dbins.open())
        throw new WsException("软件数据库无法打开");

    QSqlQuery q(dbins);
    if(!q.exec("create table if not exists items_collect ("
               "barcode text primary key not null,"
               "item_name text not null,"
               "supplier_notes text not null,"
               "ex_signal_price real not null,"
               "ex_set_price real not null,"
               "setmem_number int not null,"
               "valid_time_span int not null,"
               "valid_time_type text not null,"
               "alarm_before_days int not null,"
               "alarm_signal_atleast int not null,"
               "alarm_set_atleast int not null)"))
        throw new WsException(q.lastError().text());


}




