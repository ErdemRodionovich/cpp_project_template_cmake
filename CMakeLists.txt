cmake_minimum_required(VERSION 3.21)

set(CMAKE_DEBUG_POSTFIX _debug)

include(compiler_flags.cmake)

project(projectTemplate VERSION 0.1)

#options
#option(USE_MYMATH "use custom math library" ON)

set(
    TARGET_NAME
    projectTemplate
)
configure_file(include/configure_template.h configure.h)
set(
    HEADERS
)
set(
    SOURCES
    src/main.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})
set_target_properties(
    ${TARGET_NAME}
    PROPERTIES
        DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)

#list(APPEND EXTRA_LIBS some_lib)

target_link_libraries(${TARGET_NAME} PUBLIC ${EXTRA_LIBS} PRIVATE compiler_flags)

target_include_directories(${TARGET_NAME} PRIVATE
                                          include
                                          ${CMAKE_CURRENT_BINARY_DIR}
)

add_subdirectory(test)

#install
list(APPEND INSTALLABLE_TARGETS ${TARGET_NAME})
install(TARGETS ${INSTALLABLE_TARGETS} DESTINATION bin)
#if target is library
#install(TARGETS ${INSTALLABLE_TARGETS} EXPORT ${PROJECT_NAME}Targets DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)

#if target is library
##config for find_package
#include(CMakePackageConfigHelpers)
#configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
#  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
#  INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
#  NO_SET_AND_CHECK_MACRO
#  NO_CHECK_REQUIRED_COMPONENTS_MACRO
#)
#write_basic_package_version_file(
#  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
#  VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}"
#  COMPATIBILITY AnyNewerVersion
#)
#install(FILES
#  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
#  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
#  DESTINATION lib/cmake/${PROJECT_NAME}
#)
#export(EXPORT ${PROJECT_NAME}Targets
#  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
#)

#package installer
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_PACKAGE_DIRECTORY package)
include(CPack)