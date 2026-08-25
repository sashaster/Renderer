include(FetchContent)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.17.0
        GIT_SHALLOW TRUE
)

FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v2.0.8
        GIT_SHALLOW TRUE
        SOURCE_SUBDIR cmake
)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.5.1
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(spdlog glad glfw)
glad_add_library(glad_gl_core_41 STATIC REPRODUCIBLE LOADER API gl:core=4.1)
find_package(OpenGL REQUIRED)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_library(core STATIC ${SOURCES})
target_include_directories(core PUBLIC include)
target_link_libraries(core PUBLIC
    spdlog
    glad_gl_core_41
    glfw
    OpenGL::GL
)