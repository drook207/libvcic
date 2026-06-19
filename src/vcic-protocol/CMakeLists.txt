qt_add_library(vcic-protocol)
add_library(VCIC::vcic-protocol ALIAS vcic-protocol)

target_sources(
    vcic-protocol
    PRIVATE src/IVcicDiscoveryService.cpp
            src/VcicCamera.cpp
            src/VcicDiscoveryServiceV1.cpp
            src/VcicMessage.cpp
            src/VcicMessageCodecV1.cpp
    PUBLIC FILE_SET
           HEADERS
           BASE_DIRS
           include
           FILES
           include/vcic/IVcicDiscoveryService.h
           include/vcic/IVcicMessageCodec.h
           include/vcic/VcicCamera.h
           include/vcic/VcicCameraInfo.h
           include/vcic/VcicDiscoveryServiceV1.h
           include/vcic/VcicMessage.h
           include/vcic/VcicMessageCodecV1.h)

target_include_directories(
    vcic-protocol PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# vcic-protocol depends on vcic-transport for ITransport (used by VcicDiscoveryServiceV1). PUBLIC so
# that consumers of vcic-protocol automatically get the transport headers too.
target_link_libraries(vcic-protocol PUBLIC vcic-transport Qt6::Core Qt6::Network)

set_target_properties(
    vcic-protocol
    PROPERTIES EXPORT_NAME vcic-protocol
               VERSION ${PROJECT_VERSION}
               SOVERSION ${PROJECT_VERSION_MAJOR})

install(
    TARGETS vcic-protocol
    EXPORT VCICTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
