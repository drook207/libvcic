#include "ParameterEditorView.h"

#include "CameraSessionController.h"

namespace vcic {

ParameterEditorView::ParameterEditorView(CameraSessionController* controller, QWidget* parent)
    : QWidget(parent)
    , m_controller(controller)
{
    connect(m_controller, &CameraSessionController::parameterUpdated, this, &ParameterEditorView::onParameterUpdated);
}

void ParameterEditorView::onParameterUpdated(quint16 parameterId, const QVariant& value)
{
}

} // namespace vcic
