find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(
    vcic-gui
    main.cpp
    CameraListView.cpp
    CameraListView.h
    CameraSessionController.cpp
    CameraSessionController.h
    DiscoveryController.cpp
    DiscoveryController.h
    LogConsoleView.cpp
    LogConsoleView.h
    MainWindow.cpp
    MainWindow.h
    ParameterEditorView.cpp
    ParameterEditorView.h)

target_include_directories(vcic-gui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    vcic-gui
    PRIVATE vcic-protocol
            vcic-transport
            Qt6::Core
            Qt6::Network
            Qt6::Widgets)
