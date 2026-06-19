#pragma once

#include <QByteArray>

#include <vcic/VcicMessage.h>

namespace vcic {

class IVcicMessageCodec {
public:
    virtual ~IVcicMessageCodec() = default;

    [[nodiscard]] virtual QByteArray encode(const VcicMessage& message) const = 0;
    [[nodiscard]] virtual VcicMessage decode(const QByteArray& data) const = 0;
};

} // namespace vcic
