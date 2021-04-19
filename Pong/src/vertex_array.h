#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <stdint.h>

typedef struct VertexBuffer VertexBuffer;
typedef struct ElementBuffer ElementBuffer;

typedef struct VertexArray
{
	uint32_t id;
	VertexBuffer *vertexBuffer;
	ElementBuffer *elementBuffer;
} VertexArray;

VertexArray * vertex_array_create(void);
void vertex_array_free(VertexArray *vertexArray);

void vertex_array_bind(const VertexArray *vertexArray);
void vertex_array_set_vertex_buffer(VertexArray *vertexArray, VertexBuffer *vertexBuffer);
void vertex_array_set_element_buffer(VertexArray *vertexArray, ElementBuffer *elementBuffer);

#endif