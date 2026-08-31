#pragma once
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "Core/Config.hpp"

namespace Core {

    class OpenGLContext final{
    public:
        explicit OpenGLContext(GLFWwindow* handle): m_Handle(handle) {
            ASSERT(handle, "Window handle is null!");
        }
        void Init() const;
        void SwapBuffers() const;
        static void SetWindowHints();

        DELETE_COPY_MOVE(OpenGLContext)

    private:
        GLFWwindow* m_Handle;

    };
}
