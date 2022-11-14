cmake_minimum_required(VERSION 3.22)

set(CMAKE_DEBUG_POSTFIX _debug)

#compiler flags
add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_cxx}:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused;-Werror;-Wfloat-equal;-Wundef;-Wpointer-arith;-Wcast-align;>"
  "$<${msvc_cxx}:-W3>"
)

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

list(APPEND EXTRA_LIBS compiler_flags)

target_link_libraries(${TARGET_NAME} PUBLIC ${EXTRA_LIBS})

target_include_directories(${TARGET_NAME} PRIVATE
                                          include
                                          ${CMAKE_CURRENT_BINARY_DIR}
)

#install
list(APPEND INSTALLABLE_TARGETS ${TARGET_NAME})
install(TARGETS ${INSTALLABLE_TARGETS} DESTINATION bin)
install(FILES ${HEADERS} DESTINATION include)

add_subdirectory(test)

#package installer
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_PACKAGE_DIRECTORY package)
include(CPack)