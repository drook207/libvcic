#pragma once

#include <gmock/gmock.h>
#include <vcic/ITransport.h>

namespace vcic {

class MockTransport : public ITransport {
    Q_OBJECT

public:
    explicit MockTransport(QObject* parent = nullptr);

    MOCK_METHOD(void, connectTo, (const QString& host, quint16 port), (override));
    MOCK_METHOD(void, disconnect, (), (override));
    MOCK_METHOD(void, send, (const QByteArray& data), (override));

    // Trigger dataReceived() from a test to simulate inbound camera traffic.
    void simulateDataReceived(const QByteArray& data);
};

} // namespace vcic
