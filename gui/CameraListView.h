#pragma once

#include <QWidget>

#include <vcic/VcicCameraInfo.h>

namespace vcic {

class DiscoveryController;

class CameraListView : public QWidget {
    Q_OBJECT

public:
    explicit CameraListView(DiscoveryController* controller, QWidget* parent = nullptr);
    ~CameraListView() override = default;

signals:
    void cameraSelected(const vcic::VcicCameraInfo& info);

private slots:
    void onCamerasChanged();

private:
    DiscoveryController* m_controller{ nullptr };
};

} // namespace vcic
