include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
    GIT_SHALLOW ON)

# cmake-lint: disable=C0103
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
set(INSTALL_GTEST
    OFF
    CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

qt_add_executable(vcic-tests main.cpp mocks/MockTransport.cpp mocks/MockTransport.h)

target_include_directories(vcic-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/mocks)

target_link_libraries(
    vcic-tests
    PRIVATE GTest::gtest
            GTest::gmock
            vcic-protocol
            vcic-transport
            Qt6::Core
            Qt6::Network)

include(GoogleTest)

# PRE_TEST: discovery runs at ctest time, not at build time. This avoids the need for a display
# server / QPA plugin during the build.
gtest_discover_tests(vcic-tests PROPERTIES ENVIRONMENT "QT_QPA_PLATFORM=offscreen" DISCOVERY_MODE
                                           PRE_TEST)
