#pragma once

#include <QMainWindow>

namespace vcic {

class DiscoveryController;
class CameraSessionController;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(DiscoveryController* discoveryController,
                        CameraSessionController* sessionController,
                        QWidget* parent = nullptr);
    ~MainWindow() override = default;

private:
    void setupUi();
    void connectSignals();

    DiscoveryController* m_discoveryController{ nullptr };
    CameraSessionController* m_sessionController{ nullptr };
};

} // namespace vcic
