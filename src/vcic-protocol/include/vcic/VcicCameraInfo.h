#pragma once

#include <QHostAddress>
#include <QMetaType>
#include <QString>

namespace vcic {

struct VcicCameraInfo {
    Q_GADGET
    Q_PROPERTY(QString id MEMBER id)
    Q_PROPERTY(QString displayName MEMBER displayName)

public:
    QString id;
    QString displayName;
    QHostAddress address;
    quint16 port{ 0 };
};

} // namespace vcic

Q_DECLARE_METATYPE(vcic::VcicCameraInfo)
