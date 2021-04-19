#ifndef RENDERER_H
#define RENDERER_H

#include <cglm/vec2.h>

#include <stdint.h>

typedef struct Texture Texture;

typedef struct Renderer
{
    void(*init)(uint16_t width, uint16_t height);
    void(*shutdown)(void);
    
    void(*set_viewport)(uint16_t width, uint16_t height);
    void(*set_clear_color)(float r, float g, float b, float a);

    void(*clear)(void);

    void (*draw_texture)(vec2 position, const Texture *texture);
} Renderer;

extern Renderer renderer;

void renderer_init_instance(void);

#endif