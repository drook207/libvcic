#include <QTcpSocket>

#include <vcic/TcpTransport.h>

namespace vcic {

TcpTransport::TcpTransport(QObject* parent)
    : ITransport(parent)
    , m_socket(new QTcpSocket(this))
{
}

TcpTransport::~TcpTransport() = default;

void TcpTransport::connectTo(const QString& host, quint16 port)
{
}

void TcpTransport::disconnect()
{
}

void TcpTransport::send(const QByteArray& data)
{
}

} // namespace vcic
