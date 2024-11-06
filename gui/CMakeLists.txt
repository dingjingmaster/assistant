file(GLOB GUI_SRC
        ipc-client.cc ipc-client.h
)

include(../data/data.cmake)
include(../common/common.cmake)
include(../3thrd/singleton/singleton.cmake)

add_executable(assistant-gui
        main.cc
        tray.cc tray.h
        daemon.cc daemon.h
        ${COMMON_SRC}
        ${GUI_SRC}
        ${SINGLE_APP_GUI_SRC}
        ${DATA_RES}
)
target_include_directories(assistant-gui
        PUBLIC ${QT_INCLUDE_DIRS}
        PUBLIC ${GIO_INCLUDE_DIRS}
)

target_link_libraries(assistant-gui
        PUBLIC ${QT_LIBRARIES}
        PUBLIC ${GIO_LIBRARIES}
)