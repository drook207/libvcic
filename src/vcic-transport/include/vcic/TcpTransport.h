#pragma once

#include <vcic/ITransport.h>

class QTcpSocket;

namespace vcic {

class TcpTransport : public ITransport {
    Q_OBJECT

public:
    explicit TcpTransport(QObject* parent = nullptr);
    ~TcpTransport() override;

    void connectTo(const QString& host, quint16 port) override;
    void disconnect() override;
    void send(const QByteArray& data) override;

private:
    QTcpSocket* m_socket{ nullptr };
};

} // namespace vcic
