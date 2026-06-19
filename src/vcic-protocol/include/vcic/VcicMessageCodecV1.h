#pragma once

#include <vcic/IVcicMessageCodec.h>

namespace vcic {

// Concrete codec implementing the wire format defined in ISO 17215-3.
// Fill in message IDs, field offsets, and framing from a licensed copy of the standard.
class VcicMessageCodecV1 : public IVcicMessageCodec {
public:
    VcicMessageCodecV1() = default;
    ~VcicMessageCodecV1() override = default;

    [[nodiscard]] QByteArray encode(const VcicMessage& message) const override;
    [[nodiscard]] VcicMessage decode(const QByteArray& data) const override;
};

} // namespace vcic
