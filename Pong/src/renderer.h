#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>

typedef struct Renderer
{
    void(*init)(uint16_t width, uint16_t height);
    void(*shutdown)(void);
    
    void(*set_viewport)(uint16_t width, uint16_t height);
    void(*set_clear_color)(float r, float g, float b, float a);

    void(*clear)(void); 
} Renderer;

Renderer * renderer_get_instance(void);

#endif