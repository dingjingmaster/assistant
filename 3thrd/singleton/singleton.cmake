file(GLOB SINGLE_APP_SRC
        ${CMAKE_SOURCE_DIR}/3thrd/singleton/singleton-app.cpp
        ${CMAKE_SOURCE_DIR}/3thrd/singleton/singleton-app.h
)

file(GLOB SINGLE_APP_GUI_SRC
        ${CMAKE_SOURCE_DIR}/3thrd/singleton/singleton-app-gui.cpp
        ${CMAKE_SOURCE_DIR}/3thrd/singleton/singleton-app-gui.h)

include_directories(${CMAKE_SOURCE_DIR}/3thrd/singleton/)