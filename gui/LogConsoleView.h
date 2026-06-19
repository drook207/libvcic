#pragma once

#include <QWidget>

namespace vcic {

class CameraSessionController;

class LogConsoleView : public QWidget {
    Q_OBJECT

public:
    explicit LogConsoleView(CameraSessionController* controller, QWidget* parent = nullptr);
    ~LogConsoleView() override = default;

private slots:
    void onMessageSent(const QByteArray& raw);
    void onMessageReceived(const QByteArray& raw);

private:
    CameraSessionController* m_controller{ nullptr };
};

} // namespace vcic
