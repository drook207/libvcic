#pragma once

#include <QObject>
#include <QVariant>
#include <QVariantMap>

#include <vcic/VcicCameraInfo.h>
#include <vcic/VcicMessage.h>

namespace vcic {

class VcicCamera : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QVariantMap capabilities READ capabilities NOTIFY capabilitiesChanged)
    Q_PROPERTY(QVariantMap currentParameters READ currentParameters NOTIFY currentParametersChanged)

public:
    explicit VcicCamera(VcicCameraInfo info, QObject* parent = nullptr);
    ~VcicCamera() override = default;

    [[nodiscard]] const QString& id() const;
    [[nodiscard]] const QHostAddress& address() const;
    [[nodiscard]] const QVariantMap& capabilities() const;
    [[nodiscard]] const QVariantMap& currentParameters() const;

    void sendCommand(const VcicMessage& message);
    void requestParameter(quint16 parameterId);

signals:
    void capabilitiesChanged();
    void currentParametersChanged();
    void parameterUpdated(quint16 parameterId, const QVariant& value);
    void commandAcknowledged(quint16 messageId);
    void errorOccurred(const QString& errorString);

private:
    VcicCameraInfo m_info;
    QVariantMap m_capabilities;
    QVariantMap m_currentParameters;
};

} // namespace vcic
