cmake_minimum_required(VERSION 3.10)
project(assistant LANGUAGES C CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

add_definitions(
        -w -g -fPIC
        -D QT_NO_KEYWORDS
        -D QT_MESSAGELOGCONTEXT
        -D PACKAGE_VERSION=\\"${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}\\"
)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".so")

include_directories(${CMAKE_SOURCE_DIR})

find_package (PkgConfig)
find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)

pkg_check_modules(X REQUIRED x11)
pkg_check_modules(GIO REQUIRED gio-2.0)
pkg_check_modules(QT_CORE REQUIRED Qt5Core)
pkg_check_modules(QT REQUIRED Qt5Core Qt5Gui Qt5Network Qt5Widgets Qt5X11Extras)

message(STATUS "Qt core include     : ${QT_CORE_INCLUDE_DIRS}")
message(STATUS "Qt core libraries   : ${QT_CORE_LIBRARIES}")
message(STATUS "Qt include          : ${QT_INCLUDE_DIRS}")
message(STATUS "Qt libraries        : ${QT_LIBRARIES}")
message(STATUS "gio include         : ${GIO_INCLUDE_DIRS}")
message(STATUS "gio libraries       : ${GIO_LIBRARIES}")

add_subdirectory(gui)
add_subdirectory(service)

install(TARGETS assistant-gui DESTINATION /usr/local/assistant/bin/)
install(FILES ${CMAKE_SOURCE_DIR}/data/assistant.svg DESTINATION /usr/local/assistant/data/)
#install(FILES ${CMAKE_SOURCE_DIR}/data/assistant-gui.desktop DESTINATION /etc/xdg/autostart/)
install(FILES ${CMAKE_SOURCE_DIR}/data/assistant-gui.service DESTINATION /etc/systemd/user/)
