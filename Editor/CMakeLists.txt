project("Editor")

set(EDITOR_SOURCES
    Include/ImGui.hpp
    Source/ImGui.cpp

    Include/Editor.hpp
    Source/Editor.cpp
    Include/EditorCamera.hpp
    Source/EditorCamera.cpp
    Include/Widgets.hpp
    Source/Widgets.cpp)

add_executable(${PROJECT_NAME} ${EDITOR_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)

target_link_libraries(${PROJECT_NAME} PUBLIC ${ENGINE_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC
    ${ENGINE_INCLUDE_DIR}
)
