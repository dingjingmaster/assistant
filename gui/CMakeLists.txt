
include(../common/common.cmake)

add_executable(assistant-gui main.cc ${COMMON_SRC})
target_include_directories(assistant-gui
        PRIVATE ${QT_INCLUDE_DIRS}
)

target_link_libraries(assistant-gui
        PRIVATE ${QT_LIBRARIES}
)