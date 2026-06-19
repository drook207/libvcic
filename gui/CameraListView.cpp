#include "CameraListView.h"

#include "DiscoveryController.h"

namespace vcic {

CameraListView::CameraListView(DiscoveryController* controller, QWidget* parent)
    : QWidget(parent)
    , m_controller(controller)
{
    connect(m_controller, &DiscoveryController::camerasChanged, this, &CameraListView::onCamerasChanged);
}

void CameraListView::onCamerasChanged()
{
}

} // namespace vcic
