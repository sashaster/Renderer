
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")
add_executable(renderer ${SOURCES})
target_link_libraries(renderer PRIVATE core)