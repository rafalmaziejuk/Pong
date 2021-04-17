#include "renderer.h"

#include <glad/glad.h>

#include <stdint.h>

static uint8_t initialized;

void init(uint16_t width, uint16_t height)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void shutdown(void)
{

}

void set_viewport(uint16_t width, uint16_t height)
{
    glViewport(0, 0, width, height);
}

void set_clear_color(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void clear(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

Renderer * renderer_get_instance(void)
{
    static Renderer renderer;

    if (!initialized)
    {
        renderer.init = init;
        renderer.shutdown = shutdown;
        renderer.set_viewport = set_viewport;
        renderer.set_clear_color = set_clear_color;
        renderer.clear = clear;
        initialized = 1;
    }

    return &renderer;
}