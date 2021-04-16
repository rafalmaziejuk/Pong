#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

typedef struct GLFWwindow GLFWwindow;

typedef struct Application
{
    GLFWwindow *window;
    uint16_t windowWidth;
    uint16_t windowHeight;
} Application;

Application * application_create(const char *name, uint16_t width, uint16_t height);
void application_free(Application *app);

void application_run(Application *app);

#endif