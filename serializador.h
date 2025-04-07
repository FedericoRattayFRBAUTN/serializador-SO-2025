// serializador.h

#ifndef SERIALIZADOR_H
#define SERIALIZADOR_H

#include <stdint.h>

typedef struct {
    uint32_t size;
    uint32_t offset;
    void* stream;
} t_buffer;

t_buffer *buffer_create(uint32_t size);
void buffer_destroy(t_buffer *buffer);
void buffer_add(t_buffer *buffer, void *data, uint32_t size);
void buffer_read(t_buffer *buffer, void *data, uint32_t size);

void buffer_add_uint32(t_buffer *buffer, uint32_t data);
uint32_t buffer_read_uint32(t_buffer *buffer);

void buffer_add_uint8(t_buffer *buffer, uint8_t data);
uint8_t buffer_read_uint8(t_buffer *buffer);

void buffer_add_string(t_buffer *buffer, uint32_t length, char *string);
char *buffer_read_string(t_buffer *buffer, uint32_t *length);

#endif // SERIALIZADOR_H
