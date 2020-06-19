#include "common.h"

WsException::WsException(const QString &reason)
    :reason_store(reason),
      local_data(reason.toLocal8Bit()){}


QString WsException::reason() const noexcept
{
    return reason_store;
}


const char *WsException::what() const noexcept
{
    return local_data.data();
}
