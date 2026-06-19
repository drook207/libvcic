#pragma once

#include <QWidget>

namespace vcic {

class CameraSessionController;

class ParameterEditorView : public QWidget {
    Q_OBJECT

public:
    explicit ParameterEditorView(CameraSessionController* controller, QWidget* parent = nullptr);
    ~ParameterEditorView() override = default;

private slots:
    void onParameterUpdated(quint16 parameterId, const QVariant& value);

private:
    CameraSessionController* m_controller{ nullptr };
};

} // namespace vcic
