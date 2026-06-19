#include <QCoreApplication>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    // QCoreApplication is required so Qt's event loop and networking
    // infrastructure (QTcpSocket, QUdpSocket, etc.) are available in tests.
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("vcic-tests");

    // InitGoogleMock also initialises GoogleTest.
    testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}
