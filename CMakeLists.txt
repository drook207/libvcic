cmake_minimum_required(VERSION 3.30)

project(
    libvcic
    VERSION 0.1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# --- Options (defines all VCIC_* switches and applies global effects) --------
include(cmake/VCICOptions.cmake)

# --- Qt6 ---------------------------------------------------------------------
find_package(Qt6 REQUIRED COMPONENTS Core Network)
qt_standard_project_setup()

# --- C++ / Qt feature checks (populate VCIC_CHECKS_PASSED / _FAILED) --------
include(cmake/VCICChecks.cmake)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# --- Library targets ---------------------------------------------------------
add_subdirectory(src/vcic-protocol)
add_subdirectory(src/vcic-transport)

# --- Optional components -----------------------------------------------------
if(VCIC_BUILD_GUI)
    add_subdirectory(gui)
endif()

if(VCIC_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(VCIC_BUILD_BENCHMARKS)
    # add_subdirectory(benchmarks)
endif()

if(VCIC_BUILD_EXAMPLES)
    # add_subdirectory(examples)
endif()

# --- Package export ----------------------------------------------------------
install(
    EXPORT VCICTargets
    NAMESPACE VCIC::
    FILE VCICTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VCIC)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/VCICConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/VCICConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VCIC)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/VCICConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/VCICConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/VCICConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/VCIC)

include(CPack)

# --- Summary (always last) ---------------------------------------------------
include(cmake/VCICSummary.cmake)
vcic_print_summary()
