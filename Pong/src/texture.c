#include "texture.h"

#include <stb_image.h>
#include <glad/glad.h>

#include <assert.h>
#include <stdlib.h>

Texture * texture_create(const char *filepath)
{
    int width, height, channels;
    stbi_uc *data = stbi_load(filepath, &width, &height, &channels, 0);
    assert(data);

    Texture *newTexture = (Texture *)malloc(sizeof(Texture));
    assert(newTexture != NULL);

    newTexture->width = width;
    newTexture->height = height;

    glGenTextures(1, &newTexture->id);
    glBindTexture(GL_TEXTURE_2D, newTexture->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLenum internalFormat = 0;
    GLenum dataFormat = 0;

    if (channels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }
    else if (channels == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);

    return newTexture;
}

void texture_free(Texture *texture)
{
    glDeleteTextures(1, &texture->id);
    free(texture);
}

void texture_bind(const Texture *texture, uint32_t slot)
{
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, texture->id);
}