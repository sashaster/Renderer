#pragma once
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include "Core/Config.hpp"


namespace Renderer {

    class OpenGLContext {
    public:
        explicit OpenGLContext(GLFWwindow* handle): m_Handle(handle){}
        void Init() const;
        void SwapBuffers() const;
        static void SetWindowHints();

        DELETE_COPY_MOVE(OpenGLContext)

    private:
        GLFWwindow* m_Handle;

    };
}
