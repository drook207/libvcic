#include "LogConsoleView.h"

#include "CameraSessionController.h"

namespace vcic {

LogConsoleView::LogConsoleView(CameraSessionController* controller, QWidget* parent)
    : QWidget(parent)
    , m_controller(controller)
{
    connect(m_controller, &CameraSessionController::messageSent, this, &LogConsoleView::onMessageSent);
    connect(m_controller, &CameraSessionController::messageReceived, this, &LogConsoleView::onMessageReceived);
}

void LogConsoleView::onMessageSent(const QByteArray& raw)
{
}

void LogConsoleView::onMessageReceived(const QByteArray& raw)
{
}

} // namespace vcic
