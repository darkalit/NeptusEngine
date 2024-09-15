project("Engine" VERSION 0.0.1 DESCRIPTION "Core library of Engine")

set(ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Include PARENT_SCOPE)
set(ENGINE_NAME ${PROJECT_NAME} PARENT_SCOPE)

set(ENGINE_SOURCES
    Include/Core/API.hpp
    Include/Core/Asset.hpp
    Include/Core/Base.hpp
    Include/Core/UUID.hpp
    Source/Core/Engine.cpp
    Source/Core/UUID.cpp

    Include/Core/OS/Window.hpp
    Include/Core/OS/Filesystem.hpp
    Source/Core/OS/Window.cpp
    Source/Core/OS/Filesystem.cpp

    Include/Utils/Clock.hpp
    Include/Utils/LoadImage.hpp
    Include/Utils/Timer.hpp
    Include/Utils/Timestep.hpp
    Source/Utils/Clock.cpp
    Source/Utils/LoadImage.cpp
    Source/Utils/Timer.cpp
    Source/Utils/Timestep.cpp

    Include/Graphics/RHI/BufferLayout.hpp
    Include/Graphics/RHI/Definitions.hpp
    Include/Graphics/RHI/Framebuffer.hpp
    Include/Graphics/RHI/IndexBuffer.hpp
    Include/Graphics/RHI/Renderer.hpp
    Include/Graphics/RHI/Shader.hpp
    Include/Graphics/RHI/Texture.hpp
    Include/Graphics/RHI/VertexArrayBuffer.hpp
    Include/Graphics/RHI/VertexBuffer.hpp
    Source/Graphics/RHI/BufferLayout.cpp

    Include/Graphics/RenderPasses.hpp
    Source/Graphics/RenderPasses.cpp

    Include/Scene/Scene.hpp
    Include/Scene/SceneManager.hpp
    Include/Scene/Entity.hpp
    Source/Scene/Scene.cpp
    Source/Scene/SceneManager.cpp
    Include/Scene/Systems/BaseSystem.hpp
    Include/Scene/Systems/SystemManager.hpp
    Include/Scene/Components/BaseComponent.hpp
    Include/Scene/Components/TransformComponent.hpp
    Include/Scene/Components/IDComponent.hpp
    Include/Scene/Components/TagComponent.hpp
    Include/Scene/Components/ModelComponent.hpp
    Include/Graphics/Model.hpp
    Source/Graphics/Model.cpp
    Include/Graphics/GraphicsContext.hpp
    Source/Graphics/GraphicsContext.cpp
    Include/Utils/ResourceManager.hpp
    Source/Utils/ResourceManager.cpp
    Include/Utils/StringProcessing.hpp
    Source/Utils/StringProcessing.cpp
    Include/Core/Engine.hpp
    Source/Core/Engine.cpp
    Include/Graphics/ScreenSurface.hpp
    Source/Graphics/ScreenSurface.cpp)

if (${NEPTUS_BUILD_RENDERSYSTEM_GL})
    list(APPEND ENGINE_SOURCES
        Source/Graphics/RHI/OpenGL/GLFramebuffer.cpp
        Source/Graphics/RHI/OpenGL/GLIndexBuffer.cpp
        Source/Graphics/RHI/OpenGL/GLRenderer.cpp
        Source/Graphics/RHI/OpenGL/GLShader.cpp
        Source/Graphics/RHI/OpenGL/GLTexture.cpp
        Source/Graphics/RHI/OpenGL/GLVertexArrayBuffer.cpp
        Source/Graphics/RHI/OpenGL/GLVertexBuffer.cpp)
endif()
message(STATUS "Engine Sources: ${ENGINE_SOURCES}")


if (${NEPTUS_RUNTIME_SHARED})
    add_library(${PROJECT_NAME} SHARED ${ENGINE_SOURCES})
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${PROJECT_NAME}>
            ${RUNTIME_BUILD_DIR}/)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${PROJECT_NAME}>
            ${EDITOR_BUILD_DIR}/)

    set_target_properties(${PROJECT_NAME}
        PROPERTIES VERSION ${PROJECT_VERSION}
        PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR}
        PROPERTIES PUBLIC_HEADER ${ENGINE_INCLUDE_DIR}/NeptusEngine.hpp)
else()
    add_library(${PROJECT_NAME} STATIC ${ENGINE_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)

# =================================
# External Libs
# =================================

# SDL

add_subdirectory("External/SDL")
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2 SDL2::SDL2main)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        ${RUNTIME_BUILD_DIR}/)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        ${EDITOR_BUILD_DIR}/)

# GLAD

if(${NEPTUS_BUILD_RENDERSYSTEM_GL})
    add_subdirectory("External/glad")
    target_link_libraries(${PROJECT_NAME} PUBLIC glad)
endif()

# GLM

add_subdirectory("External/glm")
target_link_libraries(${PROJECT_NAME} PUBLIC glm)


# ENTT

add_subdirectory("External/entt")
target_link_libraries(${PROJECT_NAME} PUBLIC EnTT::EnTT)

# STB

target_include_directories(${PROJECT_NAME} PUBLIC "External/stb")
add_library(STB STATIC
    External/stb/stb_image.cpp
    External/stb/stb_image_write.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC STB)

# tiny obj

target_include_directories(${PROJECT_NAME} PUBLIC "External/tinyObj")

# imgui

set(IMGUI_DIR "External/imguiDocking")
set(IMGUI_INCLUDE_DIR ${IMGUI_DIR})
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp)

if(${NEPTUS_BUILD_RENDERSYSTEM_GL})
    list(APPEND IMGUI_SOURCES
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)
endif()

add_library(IMGUI STATIC ${IMGUI_SOURCES})
target_include_directories(IMGUI
    PUBLIC ${IMGUI_INCLUDE_DIR}
    PUBLIC ${IMGUI_INCLUDE_DIR}/backends
    PUBLIC ${IMGUI_INCLUDE_DIR}/misc/cpp
)
target_link_libraries(IMGUI PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(${PROJECT_NAME} PUBLIC IMGUI)
