#include "CameraSessionController.h"
#include "DiscoveryController.h"
#include "MainWindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("vcic-gui");
    app.setApplicationVersion("0.1.0");

    return app.exec();
}
