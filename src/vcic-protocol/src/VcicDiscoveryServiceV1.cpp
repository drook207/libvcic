#include <vcic/ITransport.h>
#include <vcic/VcicDiscoveryServiceV1.h>

namespace vcic {

VcicDiscoveryServiceV1::VcicDiscoveryServiceV1(ITransport* transport, QObject* parent)
    : IVcicDiscoveryService(parent)
    , m_transport(transport)
{
}

void VcicDiscoveryServiceV1::discoverCameras()
{
}

void VcicDiscoveryServiceV1::stopDiscovery()
{
}

} // namespace vcic
