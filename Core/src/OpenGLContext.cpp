#include <glad/gl.h>

#include "Core/OpenGLContext.hpp"

namespace Core {

    void OpenGLContext::Init() const {
        glfwMakeContextCurrent(m_Handle);
        LOG_DEBUG("Loading GLAD...");
        VERIFY(gladLoadGL(glfwGetProcAddress), "Failed to load GLAD!");
        LOG_DEBUG("GLAD initialized!");
        LOG_INFO("OpenGL: {0} {1} {2}",
            reinterpret_cast<const char*>(glGetString(GL_VENDOR)),
            reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
            reinterpret_cast<const char*>(glGetString(GL_VERSION)));
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
