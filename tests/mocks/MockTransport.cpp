#include "MockTransport.h"

namespace vcic {

MockTransport::MockTransport(QObject* parent)
    : ITransport(parent)
{
}

void MockTransport::simulateDataReceived(const QByteArray& data)
{
    emit dataReceived(data);
}

} // namespace vcic
