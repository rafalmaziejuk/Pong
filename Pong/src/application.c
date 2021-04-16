#include "application.h"
#include "renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void resize_callback(GLFWwindow *window, GLint width, GLint height)
{
    glViewport(0, 0, width, height);
}

Application * application_create(const char *name, uint16_t width, uint16_t height)
{
    Application *newApp = (Application *)malloc(sizeof(Application));
    assert(newApp != NULL);

    assert(glfwInit());
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    newApp->windowWidth = width;
    newApp->windowHeight = height;
    newApp->window = glfwCreateWindow(width, height, name, NULL, NULL);
    assert(newApp->window != NULL);

    glfwMakeContextCurrent(newApp->window);
    glfwSetFramebufferSizeCallback(newApp->window, resize_callback);
    glfwSwapInterval(1);

    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

    renderer_get_instance()->init(width, height);
    renderer_get_instance()->set_viewport(width, height);
    renderer_get_instance()->set_clear_color(0.0f, 0.0f, 0.0f, 1.0f);

    return newApp;
}

void application_free(Application *app)
{
    renderer_get_instance()->shutdown();
    glfwDestroyWindow(app->window);
    glfwTerminate();
    free(app);
}

void application_run(Application *app)
{
    float timeSinceLastUpdate = 0.0f;

    while (!glfwWindowShouldClose(app->window))
    {
        float time = (float)glfwGetTime();
        float timestep = time - timeSinceLastUpdate;
        timeSinceLastUpdate = time;

        glfwPollEvents();

        renderer_get_instance()->clear();

        

        glfwSwapBuffers(app->window);
    }
}

