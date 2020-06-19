#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <exception>


class WsException : public std::exception
{
public:
    WsException(const QString &reason);
    virtual ~WsException() override = default;

    QString reason() const noexcept;
    // exception interface
public:
    virtual const char *what() const noexcept override;

private:
    const QString reason_store;
    const QByteArray local_data;

};

#endif // COMMON_H
