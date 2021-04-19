#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <stdlib.h>

typedef enum Type
{
    NONE = 0,
    FLOAT,
    FLOAT2,
    FLOAT3,
    FLOAT4
} Type;

typedef struct VBElement
{
    uint32_t size;
    Type type;
    uint16_t offset;
    uint8_t isNormalized;

    struct VBElement *next;
} VBElement;

typedef struct BufferLayout
{
	uint32_t stride;
	VBElement *vbElements;
    uint16_t elementCount;
} BufferLayout;

BufferLayout * buffer_layout_create(void);
void buffer_layout_push_element(BufferLayout *layout, Type type, uint8_t normalized);
const VBElement * buffer_layout_get_vbelement(const BufferLayout *layout, uint8_t index);

typedef struct VertexBuffer
{
	uint32_t id;
	BufferLayout *layout;
} VertexBuffer;

VertexBuffer * vertex_buffer_create(const float *data, uint32_t size, BufferLayout *layout);
void vertex_buffer_free(VertexBuffer *buffer);
void vertex_buffer_bind(const VertexBuffer *buffer);

typedef struct ElementBuffer
{
	uint32_t id;
	uint32_t elementCount;
} ElementBuffer;

ElementBuffer * element_buffer_create(const uint32_t *data, uint32_t elementCount);
void element_buffer_free(ElementBuffer *buffer);
void element_buffer_bind(const ElementBuffer *buffer);

#endif