project("Runtime")

set(RUNTIME_SOURCES
    Include/Application.hpp
    Source/Application.cpp)

if(WIN32)
    list(APPEND RUNTIME_SOURCES
        Windows/WindowsLaunch.cpp)
endif()

add_executable(${PROJECT_NAME} ${RUNTIME_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)

target_link_libraries(${PROJECT_NAME} PUBLIC ${ENGINE_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC
    ${ENGINE_INCLUDE_DIR}
)
