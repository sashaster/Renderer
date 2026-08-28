
#include <glad/gl.h>
#include "Core/OpenGLContext.hpp"

namespace Renderer {

    void OpenGLContext::Init() const {
        glfwMakeContextCurrent(m_Handle);
        LOG_DEBUG("Loading GLAD...");
        ASSERT(gladLoadGL(glfwGetProcAddress), "Failed to load GLAD!");
        LOG_DEBUG("GLAD initialized!");
    }

    void OpenGLContext::SetWindowHints() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

    void OpenGLContext::SwapBuffers() const {
        glfwSwapBuffers(m_Handle);
    }
}
