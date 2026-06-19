#pragma once

#include <vcic/IVcicDiscoveryService.h>

namespace vcic {

class ITransport;

// Concrete discovery implementation following the procedure defined in ISO 17215-2.
// Fill in the broadcast address, port, and request/response format from the standard.
class VcicDiscoveryServiceV1 : public IVcicDiscoveryService {
    Q_OBJECT

public:
    explicit VcicDiscoveryServiceV1(ITransport* transport, QObject* parent = nullptr);
    ~VcicDiscoveryServiceV1() override = default;

    void discoverCameras() override;
    void stopDiscovery() override;

private:
    ITransport* m_transport{ nullptr };
};

} // namespace vcic
