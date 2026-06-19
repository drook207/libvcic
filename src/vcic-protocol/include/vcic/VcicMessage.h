#pragma once

#include <QByteArray>
#include <QDateTime>
#include <QMetaType>

namespace vcic {

class VcicMessage {
public:
    VcicMessage() = default;
    VcicMessage(quint16 messageId, QByteArray payload);

    [[nodiscard]] quint16 messageId() const;
    void setMessageId(quint16 messageId);

    [[nodiscard]] const QByteArray& payload() const;
    void setPayload(const QByteArray& payload);

    [[nodiscard]] const QDateTime& timestamp() const;

    [[nodiscard]] bool isValid() const;

private:
    quint16 m_messageId{ 0 };
    QByteArray m_payload;
    QDateTime m_timestamp;
};

} // namespace vcic

Q_DECLARE_METATYPE(vcic::VcicMessage)
