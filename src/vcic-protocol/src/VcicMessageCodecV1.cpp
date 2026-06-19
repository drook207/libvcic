#include <vcic/VcicMessageCodecV1.h>

namespace vcic {

QByteArray VcicMessageCodecV1::encode(const VcicMessage& message) const
{
    return {};
}

VcicMessage VcicMessageCodecV1::decode(const QByteArray& data) const
{
    return {};
}

} // namespace vcic
