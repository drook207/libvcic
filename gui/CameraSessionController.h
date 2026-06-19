#pragma once

#include <QObject>
#include <QVariant>

#include <vcic/VcicCameraInfo.h>
#include <vcic/VcicMessage.h>

namespace vcic {

class IVcicMessageCodec;
class ITransport;
class VcicCamera;

class CameraSessionController : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectionStateChanged)

public:
    explicit CameraSessionController(IVcicMessageCodec* codec, ITransport* transport, QObject* parent = nullptr);
    ~CameraSessionController() override = default;

    bool isConnected() const;

public slots:
    void connectToCamera(const vcic::VcicCameraInfo& info);
    void disconnectCamera();
    void requestParameter(quint16 parameterId);
    void sendCommand(quint16 messageId, const QByteArray& payload = {});

signals:
    void connectionStateChanged();
    void parameterUpdated(quint16 parameterId, const QVariant& value);
    void messageSent(const QByteArray& raw);
    void messageReceived(const QByteArray& raw);
    void errorOccurred(const QString& errorString);

private slots:
    void onDataReceived(const QByteArray& data);
    void onTransportError(const QString& errorString);

private:
    IVcicMessageCodec* m_codec{ nullptr };
    ITransport* m_transport{ nullptr };
    VcicCamera* m_camera{ nullptr };
};

} // namespace vcic
