#pragma once

#include <vcic/ITransport.h>

class QUdpSocket;

namespace vcic {

class UdpTransport : public ITransport {
    Q_OBJECT

public:
    explicit UdpTransport(QObject* parent = nullptr);
    ~UdpTransport() override;

    void connectTo(const QString& host, quint16 port) override;
    void disconnect() override;
    void send(const QByteArray& data) override;

private:
    QUdpSocket* m_socket{ nullptr };
    QString m_host;
    quint16 m_port{ 0 };
};

} // namespace vcic
