cmake_minimum_required(VERSION 3.22)
project(camoverlay VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------- OpenCV ----------------
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/../opencv/build")
find_package(OpenCV REQUIRED)

# ---------------- GLFW (binary) ----------------
set(GLFW_ROOT "${CMAKE_SOURCE_DIR}/glfw3")

# Import GLFW as a shared library
add_library(glfw SHARED IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_IMPLIB   "${GLFW_ROOT}/lib-vc2022/glfw3.lib"
    IMPORTED_LOCATION "${GLFW_ROOT}/lib-vc2022/glfw3.dll"
    INTERFACE_INCLUDE_DIRECTORIES "${GLFW_ROOT}/include" # absolute path
)

# ---------------- ImGui ----------------
add_library(imgui
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    "${CMAKE_SOURCE_DIR}"           # ImGui sources
    "${GLFW_ROOT}/include"          # GLFW headers
)

# ---------------- Executable ----------------
add_executable(camoverlay main.cpp)

target_link_libraries(camoverlay
    PRIVATE
    imgui
    glfw
    ${OpenCV_LIBS}
    opengl32
)

# ---------------- MSVC Compile Options ----------------
if(MSVC)
    target_compile_options(camoverlay PRIVATE /EHsc)
endif()

# ---------------- Copy DLLs Next to EXE ----------------
add_custom_command(TARGET camoverlay POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${OpenCV_DIR}/x64/vc16/bin/opencv_world4130.dll"
        "${OpenCV_DIR}/x64/vc16/bin/opencv_videoio_ffmpeg4130_64.dll"
        $<TARGET_FILE_DIR:camoverlay>
)

add_custom_command(TARGET camoverlay POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${GLFW_ROOT}/lib-vc2022/glfw3.dll"
        $<TARGET_FILE_DIR:camoverlay>
)
