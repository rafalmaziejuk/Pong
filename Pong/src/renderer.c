#include "renderer.h"
#include "buffer.h"
#include "vertex_array.h"
#include "shader.h"
#include "texture.h"

#include <glad/glad.h>
#include <cglm/cglm.h>

#include <stdint.h>

typedef struct Data
{
	mat4 projectionMatrix;
	Shader *spriteShader;
	VertexArray *spriteVertexArray;
} Data;

static Data rendererData;

Renderer renderer;

static void init(uint16_t width, uint16_t height)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm_ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f, rendererData.projectionMatrix);
	rendererData.spriteShader = shader_create("Pong/assets/sprite.glsl");
	rendererData.spriteVertexArray = vertex_array_create();

	shader_bind(rendererData.spriteShader);
	shader_set_int(rendererData.spriteShader, "sprite", 0);
	shader_set_mat4(rendererData.spriteShader, "projection", rendererData.projectionMatrix);

	//Quad with origin in its center
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, //bottom-left
		 0.5f, -0.5f, 1.0f, 0.0f, //bottom-right
		 0.5f,  0.5f, 1.0f, 1.0f, //top-right
		-0.5f,  0.5f, 0.0f, 1.0f  //top-left
	};

    BufferLayout *layout = buffer_layout_create();
    buffer_layout_push_element(layout, FLOAT4, 0);
    
    VertexBuffer *vbo = vertex_buffer_create(vertices, sizeof(vertices), layout);
	vertex_array_set_vertex_buffer(rendererData.spriteVertexArray, vbo);

	uint32_t indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	ElementBuffer *ebo = element_buffer_create(indices, sizeof(indices) / sizeof(uint32_t));
	vertex_array_set_element_buffer(rendererData.spriteVertexArray, ebo);
}

static void shutdown(void)
{
    shader_free(rendererData.spriteShader);
    vertex_array_free(rendererData.spriteVertexArray);
}

static void set_viewport(uint16_t width, uint16_t height)
{
    glViewport(0, 0, width, height);
}

static void set_clear_color(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

static void clear(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

static void draw_texture(vec2 position, const Texture *texture)
{
	mat4 model =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

	glm_translate(model, (vec3){ position[0], position[1], 0.0f });
    glm_scale(model, (vec3){ texture->width, texture->height, 1.0f });

	shader_bind(rendererData.spriteShader);
	shader_set_mat4(rendererData.spriteShader, "model", model);

	texture_bind(texture, GL_TEXTURE0);

	vertex_array_bind(rendererData.spriteVertexArray);
	glDrawElements(GL_TRIANGLES, rendererData.spriteVertexArray->elementBuffer->elementCount, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void renderer_init_instance(void)
{
    renderer.init = init;
    renderer.shutdown = shutdown;
    renderer.set_viewport = set_viewport;
    renderer.set_clear_color = set_clear_color;
    renderer.clear = clear;
    renderer.draw_texture = draw_texture;
}