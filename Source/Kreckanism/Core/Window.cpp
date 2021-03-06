#include <Kreckanism/Core/Window.h>

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Kreckanism/Core/Logger.h>
#include <Kreckanism/Event/KeyPressEvent.h>
#include <Kreckanism/Event/MouseMoveEvent.h>
#include <Kreckanism/Event/MousePressEvent.h>
#include <Kreckanism/Event/MouseReleaseEvent.h>
#include <Kreckanism/Event/WindowResizeEvent.h>

namespace Ksm
{
    Window::Window(int width, int height, const std::string& title) : width(width), height(height), title(title)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if (window == nullptr)
        {
            KLOG_FAIL("Failed to create window.");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            KLOG_FAIL("Failed to load GLAD.");
            glfwTerminate();
            return;
        }

        glViewport(0, 0, width, height);

        glfwSetWindowUserPointer(window, this);

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            const auto& self = *static_cast<Window*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressEvent e(key);
                    self.eventCallback(e);
                    return;
                }
                case GLFW_REPEAT:
                {
                    KeyPressEvent e(key);
                    self.eventCallback(e);
                    return;
                }
            }
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y)
        {
            const auto& self = *static_cast<Window*>(glfwGetWindowUserPointer(window));

            MouseMoveEvent e(x, y);
            self.eventCallback(e);
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
        {
            const auto& self = *static_cast<Window*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MousePressEvent e(button);
                    self.eventCallback(e);
                    return;
                }
                case GLFW_RELEASE:
                {
                    MouseReleaseEvent e(button);
                    self.eventCallback(e);
                    return;
                }
            }
        });

        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            const auto& self = *static_cast<Window*>(glfwGetWindowUserPointer(window));

            glViewport(0, 0, width, height);

            WindowResizeEvent e(width, height);
            self.eventCallback(e);
        });
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    void Window::SetEventCallback(const std::function<void(Event&)>& callback)
    {
        this->eventCallback = callback;
    }

    GLFWwindow* Window::GetWindow() const
    {
        return window;
    }

    void Window::SetTitle(std::string title) const
    {
        glfwSetWindowTitle(window, title.c_str());
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(window);
    }

    void Window::Update() const
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    int Window::GetWidth() const
    {
        return width;
    }

    int Window::GetHeight() const
    {
        return height;
    }
}
