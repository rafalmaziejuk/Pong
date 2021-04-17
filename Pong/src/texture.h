#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>

typedef struct Texture
{
    uint32_t id;
    uint16_t width;
    uint16_t height;
} Texture;

Texture * texture_create(const char *filepath);
void texture_free(Texture *texture);

void texture_bind(const Texture *texture, uint32_t slot);

#endif