file(GLOB SERVICE_SRC
        ipc-service.cc      ipc-service.h
)

include(../common/common.cmake)

add_executable(assistant-service main.cc ${COMMON_SRC} ${SERVICE_SRC})
target_include_directories(assistant-service
        PRIVATE ${QT_CORE_INCLUDE_DIRS}
        PRIVATE ${GIO_INCLUDE_DIRS}
)
target_link_libraries(assistant-service
        PRIVATE ${QT_CORE_LIBRARIES}
        PRIVATE ${GIO_LIBRARIES}
)
