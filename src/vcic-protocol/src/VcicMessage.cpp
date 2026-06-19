#include <vcic/VcicMessage.h>

namespace vcic {

VcicMessage::VcicMessage(quint16 messageId, QByteArray payload)
    : m_messageId(messageId)
    , m_payload(std::move(payload))
    , m_timestamp(QDateTime::currentDateTimeUtc())
{
}

quint16 VcicMessage::messageId() const
{
    return m_messageId;
}

void VcicMessage::setMessageId(quint16 messageId)
{
    m_messageId = messageId;
}

const QByteArray& VcicMessage::payload() const
{
    return m_payload;
}

void VcicMessage::setPayload(const QByteArray& payload)
{
    m_payload = payload;
}

const QDateTime& VcicMessage::timestamp() const
{
    return m_timestamp;
}

bool VcicMessage::isValid() const
{
    return false;
}

} // namespace vcic
