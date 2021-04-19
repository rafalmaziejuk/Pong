#include "buffer.h"

#include <glad/glad.h>

#include <stdlib.h>
#include <assert.h>

static uint8_t get_type_size(Type type)
{
	switch (type)
	{
		case FLOAT:  return 1 * sizeof(float);
		case FLOAT2: return 2 * sizeof(float);
		case FLOAT3: return 3 * sizeof(float);
		case FLOAT4: return 4 * sizeof(float);
	}

	return 0;
}

static void calculate_stride(BufferLayout *bufferLayout)
{
    uint16_t offset = 0;
    for (VBElement *it = bufferLayout->vbElements; it != NULL; it = it->next)
    {
        it->offset = offset;
        bufferLayout->stride += it->size;
        offset += it->size;
    }
}

static VBElement * vbelement_create(Type type, uint8_t normalized)
{
    VBElement *newElement = (VBElement *)malloc(sizeof *newElement);
    assert(newElement != NULL);

    newElement->size = get_type_size(type);
    newElement->type = type;
    newElement->offset = 0;
    newElement->isNormalized = normalized;
    newElement->next = NULL;

    return newElement;
}

BufferLayout * buffer_layout_create(void)
{
    BufferLayout *newLayout = (BufferLayout *)malloc(sizeof *newLayout);
    assert(newLayout != NULL);

    newLayout->stride = 0;
    newLayout->vbElements = NULL;
    newLayout->elementCount = 0;

	return newLayout;
}

static void bufferlayout_free(BufferLayout *layout)
{
    while (layout->vbElements != NULL)
    {
        VBElement *it = layout->vbElements;
        layout->vbElements = layout->vbElements->next;
        free(it);
    }

    free(layout);
}

void buffer_layout_push_element(BufferLayout *layout, Type type, uint8_t normalized)
{
    if (layout->vbElements == NULL)
        layout->vbElements = vbelement_create(type, normalized);
    else
    {
        VBElement *it = layout->vbElements;
        while (it->next != NULL)
            it = it->next;

        it->next = vbelement_create(type, normalized);
    }

    calculate_stride(layout);
    layout->elementCount++;
}

const VBElement * buffer_layout_get_vbelement(const BufferLayout *layout, uint8_t index)
{
	VBElement *it = layout->vbElements;
	uint8_t counter = 0;

	while (index != counter && it->next != NULL)
	{
		it = it->next;
		counter++;
	}

	return it;
}

VertexBuffer * vertex_buffer_create(const float *data, uint32_t size, BufferLayout *layout)
{
    VertexBuffer *newBuffer = (VertexBuffer *)malloc(sizeof *newBuffer);
    assert(newBuffer != NULL);

    newBuffer->layout = layout;
    glGenBuffers(1, &newBuffer->id);
	glBindBuffer(GL_ARRAY_BUFFER, newBuffer->id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	return newBuffer;
}

void vertex_buffer_free(VertexBuffer *buffer)
{
    bufferlayout_free(buffer->layout);
    glDeleteBuffers(1, &buffer->id);
    free(buffer);
}

void vertex_buffer_bind(const VertexBuffer *buffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
}

ElementBuffer * element_buffer_create(const uint32_t *data, uint32_t elementCount)
{
    ElementBuffer *newBuffer = (ElementBuffer *)malloc(sizeof *newBuffer);
    assert(newBuffer != NULL);

    newBuffer->elementCount = elementCount;
    glGenBuffers(1, &newBuffer->id);
	glBindBuffer(GL_ARRAY_BUFFER, newBuffer->id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uint32_t) * newBuffer->elementCount, data, GL_STATIC_DRAW);

	return newBuffer;
}

void element_buffer_free(ElementBuffer *buffer)
{
    glDeleteBuffers(1, &buffer->id);
    free(buffer);
}

void element_buffer_bind(const ElementBuffer *buffer)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->id);
}