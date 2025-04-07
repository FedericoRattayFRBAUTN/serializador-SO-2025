#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Estructura genérica para manejar un buffer de datos serializados
typedef struct {
    uint32_t size;   // Tamaño total del stream (en bytes)
    uint32_t offset; // Posición actual de lectura/escritura
    void* stream;    // Stream binario que almacena los datos
} t_buffer;

// Crea un nuevo buffer con espacio para 'size' bytes
t_buffer *buffer_create(uint32_t size) {
    t_buffer* buffer = malloc(sizeof(t_buffer));
    buffer->size = size;
    buffer->offset = 0;
    buffer->stream = malloc(size);
    return buffer;
}

// Libera toda la memoria asociada al buffer
void buffer_destroy(t_buffer *buffer) {
    if (buffer) {
        free(buffer->stream);
        free(buffer);
    }
}

// Agrega un bloque de datos de tamaño 'size' al stream desde 'data'
void buffer_add(t_buffer *buffer, void *data, uint32_t size) {
    memcpy(buffer->stream + buffer->offset, data, size);
    buffer->offset += size;
}

// Lee 'size' bytes del stream y los guarda en 'data'
void buffer_read(t_buffer *buffer, void *data, uint32_t size) {
    memcpy(data, buffer->stream + buffer->offset, size);
    buffer->offset += size;
}

// Agrega un uint32_t (entero de 4 bytes) al buffer
void buffer_add_uint32(t_buffer *buffer, uint32_t data) {
    buffer_add(buffer, &data, sizeof(uint32_t));
}

// Lee un uint32_t del buffer
uint32_t buffer_read_uint32(t_buffer *buffer) {
    uint32_t data;
    buffer_read(buffer, &data, sizeof(uint32_t));
    return data;
}

// Agrega un uint8_t (entero de 1 byte) al buffer
void buffer_add_uint8(t_buffer *buffer, uint8_t data) {
    buffer_add(buffer, &data, sizeof(uint8_t));
}

// Lee un uint8_t del buffer
uint8_t buffer_read_uint8(t_buffer *buffer) {
    uint8_t data;
    buffer_read(buffer, &data, sizeof(uint8_t));
    return data;
}

// Agrega un string al buffer:
// Primero guarda su longitud (uint32_t), luego el contenido del string (sin importar si tiene '\0')
void buffer_add_string(t_buffer *buffer, uint32_t length, char *string) {
    buffer_add_uint32(buffer, length);     // Longitud del string
    buffer_add(buffer, string, length);    // Contenido del string
}

// Lee un string del buffer:
// Devuelve un puntero al string leído, y guarda la longitud en '*length'
char *buffer_read_string(t_buffer *buffer, uint32_t *length) {
    *length = buffer_read_uint32(buffer);       // Leer la longitud
    char *string = malloc(*length);             // Reservar memoria para el string
    buffer_read(buffer, string, *length);       // Leer el contenido
    return string;
}
