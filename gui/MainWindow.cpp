#include "MainWindow.h"

#include "CameraListView.h"
#include "CameraSessionController.h"
#include "DiscoveryController.h"
#include "LogConsoleView.h"
#include "ParameterEditorView.h"

namespace vcic {

MainWindow::MainWindow(DiscoveryController* discoveryController,
                       CameraSessionController* sessionController,
                       QWidget* parent)
    : QMainWindow(parent)
    , m_discoveryController(discoveryController)
    , m_sessionController(sessionController)
{
    setupUi();
    connectSignals();
}

void MainWindow::setupUi()
{
}

void MainWindow::connectSignals()
{
}

} // namespace vcic
