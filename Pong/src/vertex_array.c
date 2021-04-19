#include "vertex_array.h"
#include "buffer.h"

#include <glad/glad.h>

#include <assert.h>
#include <stdlib.h>

static GLenum get_opengl_data_type(Type type)
{
	switch (type)
	{
		case FLOAT:  return GL_FLOAT;
		case FLOAT2: return GL_FLOAT;
		case FLOAT3: return GL_FLOAT;
		case FLOAT4: return GL_FLOAT;
	}

	return 0;
}

static uint8_t get_component_count(Type type)
{
	switch (type)
	{
		case FLOAT:  return 1;
		case FLOAT2: return 2;
		case FLOAT3: return 3;
		case FLOAT4: return 4;
	}

	return 0;
}

VertexArray * vertex_array_create(void)
{
	VertexArray *newVertexArray = (VertexArray *)malloc(sizeof *newVertexArray);
	assert(newVertexArray != NULL);

	glGenVertexArrays(1, &newVertexArray->id);

	return newVertexArray;
}

void vertex_array_free(VertexArray *vertexArray)
{
	vertex_buffer_free(vertexArray->vertexBuffer);
	element_buffer_free(vertexArray->elementBuffer);
	free(vertexArray);
}

void vertex_array_bind(const VertexArray *vertexArray)
{
	glBindVertexArray(vertexArray->id);
}

void vertex_array_set_vertex_buffer(VertexArray *vertexArray, VertexBuffer *vertexBuffer)
{
	vertex_array_bind(vertexArray);
	vertex_buffer_bind(vertexBuffer);

	//Iterate through layout's vertex buffer elements
	const BufferLayout *layout = vertexBuffer->layout;
	for (uint8_t i = 0; i < layout->elementCount; i++)
	{
		const VBElement *element = buffer_layout_get_vbelement(layout, i);

		glEnableVertexAttribArray(i);
		glVertexAttribPointer
		(
			i,
			get_component_count(element->type),
			get_opengl_data_type(element->type),
			element->isNormalized ? GL_TRUE : GL_FALSE,
			layout->stride,
			(const void *)element->offset
		);
	}

	vertexArray->vertexBuffer = vertexBuffer;
}

void vertex_array_set_element_buffer(VertexArray *vertexArray, ElementBuffer *elementBuffer)
{
	vertex_array_bind(vertexArray);
	element_buffer_bind(elementBuffer);
	vertexArray->elementBuffer = elementBuffer;
}