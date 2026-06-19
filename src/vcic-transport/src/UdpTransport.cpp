#include <QUdpSocket>

#include <vcic/UdpTransport.h>

namespace vcic {

UdpTransport::UdpTransport(QObject* parent)
    : ITransport(parent)
    , m_socket(new QUdpSocket(this))
{
}

UdpTransport::~UdpTransport() = default;

void UdpTransport::connectTo(const QString& host, quint16 port)
{
}

void UdpTransport::disconnect()
{
}

void UdpTransport::send(const QByteArray& data)
{
}

} // namespace vcic
