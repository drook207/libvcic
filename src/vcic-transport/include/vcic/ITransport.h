#pragma once

#include <QByteArray>
#include <QObject>
#include <QString>

namespace vcic {

class ITransport : public QObject {
    Q_OBJECT

public:
    explicit ITransport(QObject* parent = nullptr);
    ~ITransport() override = default;

    virtual void connectTo(const QString& host, quint16 port) = 0;
    virtual void disconnect() = 0;
    virtual void send(const QByteArray& data) = 0;

signals:
    void connected();
    void disconnected();
    void dataReceived(const QByteArray& data);
    void errorOccurred(const QString& errorString);
};

} // namespace vcic
