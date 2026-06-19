qt_add_library(vcic-transport)
add_library(VCIC::vcic-transport ALIAS vcic-transport)

target_sources(
    vcic-transport
    PRIVATE src/ITransport.cpp src/TcpTransport.cpp src/UdpTransport.cpp
    PUBLIC FILE_SET
           HEADERS
           BASE_DIRS
           include
           FILES
           include/vcic/ITransport.h
           include/vcic/TcpTransport.h
           include/vcic/UdpTransport.h)

target_include_directories(
    vcic-transport PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                          $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(vcic-transport PUBLIC Qt6::Core Qt6::Network)

set_target_properties(
    vcic-transport
    PROPERTIES EXPORT_NAME vcic-transport
               VERSION ${PROJECT_VERSION}
               SOVERSION ${PROJECT_VERSION_MAJOR})

install(
    TARGETS vcic-transport
    EXPORT VCICTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
