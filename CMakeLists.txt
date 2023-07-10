cmake_minimum_required(VERSION 3.18)
project(pi-lookup VERSION 0.1.0)

#
# Define the library
#

include(GNUInstallDirs)
add_library(pi-lookup INTERFACE)
add_library(pi::lookup ALIAS pi-lookup)
target_compile_features(pi-lookup INTERFACE cxx_std_20)

target_include_directories(pi-lookup INTERFACE
    $<BUILD_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_sources(pi-lookup INTERFACE
    $<BUILD_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include/pi/containers/lookup_table.hpp>)

#
# Export and Install library targets
#

install(TARGETS pi-lookup
        EXPORT pi-lookup-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

export(EXPORT pi-lookup-targets
       FILE ${CMAKE_CURRENT_BINARY_DIR}/lookup-targets.cmake
       NAMESPACE pi::)

install(EXPORT pi-lookup-targets
        FILE lookup-targets.cmake
        NAMESPACE pi::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pi)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#
# Create and Install package
#

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/lookup-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/lookup-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/lookup-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pi)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/lookup-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/lookup-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pi)

export(PACKAGE pi-lookup)
