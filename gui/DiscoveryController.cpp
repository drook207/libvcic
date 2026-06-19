#include "DiscoveryController.h"

#include <vcic/IVcicDiscoveryService.h>

namespace vcic {

DiscoveryController::DiscoveryController(IVcicDiscoveryService* service, QObject* parent)
    : QObject(parent)
    , m_service(service)
{
    connect(m_service, &IVcicDiscoveryService::cameraFound, this, &DiscoveryController::onCameraFound);
}

QList<VcicCameraInfo> DiscoveryController::cameras() const
{
    return m_cameras;
}

void DiscoveryController::startDiscovery()
{
    m_service->discoverCameras();
}

void DiscoveryController::stopDiscovery()
{
    m_service->stopDiscovery();
}

void DiscoveryController::onCameraFound(const VcicCameraInfo& info)
{
    m_cameras.append(info);
    emit camerasChanged();
}

} // namespace vcic
