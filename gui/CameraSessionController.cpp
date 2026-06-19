#include "CameraSessionController.h"

#include <vcic/ITransport.h>
#include <vcic/IVcicMessageCodec.h>
#include <vcic/VcicCamera.h>

namespace vcic {

CameraSessionController::CameraSessionController(IVcicMessageCodec* codec, ITransport* transport, QObject* parent)
    : QObject(parent)
    , m_codec(codec)
    , m_transport(transport)
{
    connect(m_transport, &ITransport::dataReceived, this, &CameraSessionController::onDataReceived);
    connect(m_transport, &ITransport::errorOccurred, this, &CameraSessionController::onTransportError);
}

bool CameraSessionController::isConnected() const
{
    return m_camera != nullptr;
}

void CameraSessionController::connectToCamera(const VcicCameraInfo& info)
{
}

void CameraSessionController::disconnectCamera()
{
}

void CameraSessionController::requestParameter(quint16 parameterId)
{
}

void CameraSessionController::sendCommand(quint16 messageId, const QByteArray& payload)
{
}

void CameraSessionController::onDataReceived(const QByteArray& data)
{
    emit messageReceived(data);
}

void CameraSessionController::onTransportError(const QString& errorString)
{
    emit errorOccurred(errorString);
}

} // namespace vcic
