#pragma once

#include <QList>
#include <QObject>

#include <vcic/VcicCameraInfo.h>

namespace vcic {

class IVcicDiscoveryService;

class DiscoveryController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<vcic::VcicCameraInfo> cameras READ cameras NOTIFY camerasChanged)

public:
    explicit DiscoveryController(IVcicDiscoveryService* service, QObject* parent = nullptr);
    ~DiscoveryController() override = default;

    QList<vcic::VcicCameraInfo> cameras() const;

public slots:
    void startDiscovery();
    void stopDiscovery();

signals:
    void camerasChanged();

private slots:
    void onCameraFound(const vcic::VcicCameraInfo& info);

private:
    IVcicDiscoveryService* m_service{ nullptr };
    QList<vcic::VcicCameraInfo> m_cameras;
};

} // namespace vcic
