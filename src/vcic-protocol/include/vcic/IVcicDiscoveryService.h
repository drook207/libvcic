#pragma once

#include <QList>
#include <QObject>

#include <vcic/VcicCameraInfo.h>

namespace vcic {

class IVcicDiscoveryService : public QObject {
    Q_OBJECT

public:
    explicit IVcicDiscoveryService(QObject* parent = nullptr);
    ~IVcicDiscoveryService() override = default;

    virtual void discoverCameras() = 0;
    virtual void stopDiscovery() = 0;

signals:
    void cameraFound(const vcic::VcicCameraInfo& info);
    void discoveryFinished();
};

} // namespace vcic
