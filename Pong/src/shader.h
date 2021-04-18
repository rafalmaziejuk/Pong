#ifndef SHADER_H
#define SHADER_H

#include <cglm/vec3.h>

#include <stdint.h>

typedef struct Shader
{
    uint32_t id;
} Shader;

Shader * shader_create(const char *filepath);
void shader_free(Shader *shader);

void shader_bind(const Shader *shader);

void shader_set_int(const Shader *shader, const char *name, int value);
void shader_set_float(const Shader *shader, const char *name, float value);
void shader_set_vec3f(const Shader *shader, const char *name, vec3 vec);
void shader_set_mat4(const Shader *shader, const char *name, mat4 mat);

#endif