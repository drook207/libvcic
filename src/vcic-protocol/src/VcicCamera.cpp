#include <vcic/VcicCamera.h>

namespace vcic {

VcicCamera::VcicCamera(VcicCameraInfo info, QObject* parent)
    : QObject(parent)
    , m_info(std::move(info))
{
}

const QString& VcicCamera::id() const
{
    return m_info.id;
}

const QHostAddress& VcicCamera::address() const
{
    return m_info.address;
}

const QVariantMap& VcicCamera::capabilities() const
{
    return m_capabilities;
}

const QVariantMap& VcicCamera::currentParameters() const
{
    return m_currentParameters;
}

void VcicCamera::sendCommand(const VcicMessage& message)
{
}

void VcicCamera::requestParameter(quint16 parameterId)
{
}

} // namespace vcic
