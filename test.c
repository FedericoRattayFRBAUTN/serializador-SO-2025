// test.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serializador.h"

// -----------------------------------------
// ESTRUCTURAS DE PRUEBA
// -----------------------------------------

typedef struct {
    uint32_t dni;
    uint8_t edad;
    uint32_t pasaporte;
    uint32_t nombre_length;
    char* nombre;
} t_persona;

typedef struct {
    uint32_t id;
    float precio;
    uint32_t nombre_length;
    char* nombre;
} t_producto;

// -----------------------------------------
// SERIALIZACIÓN / DESERIALIZACIÓN PERSONA
// -----------------------------------------

t_buffer* persona_serializar(t_persona* p) {
    t_buffer* buffer = buffer_create(
        sizeof(uint32_t) * 3 + sizeof(uint8_t) + sizeof(uint32_t) + p->nombre_length
    );
    buffer_add_uint32(buffer, p->dni);
    buffer_add_uint8(buffer, p->edad);
    buffer_add_uint32(buffer, p->pasaporte);
    buffer_add_string(buffer, p->nombre_length, p->nombre);
    return buffer;
}

t_persona* persona_deserializar(t_buffer* buffer) {
    t_persona* p = malloc(sizeof(t_persona));
    p->dni = buffer_read_uint32(buffer);
    p->edad = buffer_read_uint8(buffer);
    p->pasaporte = buffer_read_uint32(buffer);
    p->nombre = buffer_read_string(buffer, &p->nombre_length);
    return p;
}

// -----------------------------------------
// SERIALIZACIÓN / DESERIALIZACIÓN PRODUCTO
// -----------------------------------------

t_buffer* producto_serializar(t_producto* pr) {
    t_buffer* buffer = buffer_create(
        sizeof(uint32_t) + sizeof(float) + sizeof(uint32_t) + pr->nombre_length
    );
    buffer_add_uint32(buffer, pr->id);
    buffer_add(buffer, &(pr->precio), sizeof(float));
    buffer_add_string(buffer, pr->nombre_length, pr->nombre);
    return buffer;
}

t_producto* producto_deserializar(t_buffer* buffer) {
    t_producto* pr = malloc(sizeof(t_producto));
    pr->id = buffer_read_uint32(buffer);
    buffer_read(buffer, &(pr->precio), sizeof(float));
    pr->nombre = buffer_read_string(buffer, &pr->nombre_length);
    return pr;
}

// -----------------------------------------
// FUNCIÓN PRINCIPAL DE PRUEBA
// -----------------------------------------

int main() {
    printf("=== Caso de prueba 1: Persona ===\n");

    t_persona persona = { .dni = 12345678, .edad = 30, .pasaporte = 998877,
                          .nombre_length = 6, .nombre = strdup("Juan\n") };

    t_buffer* buffer_p = persona_serializar(&persona);
    buffer_p->offset = 0; // Reset para deserializar
    t_persona* persona_recibida = persona_deserializar(buffer_p);

    printf("DNI: %u\n", persona_recibida->dni);
    printf("Edad: %u\n", persona_recibida->edad);
    printf("Pasaporte: %u\n", persona_recibida->pasaporte);
    printf("Nombre: %s", persona_recibida->nombre);

    free(persona_recibida->nombre);
    free(persona_recibida);
    buffer_destroy(buffer_p);


    printf("\n=== Caso de prueba 2: Producto ===\n");

    t_producto prod = { .id = 1001, .precio = 259.99f,
                        .nombre_length = 11, .nombre = strdup("Auriculares") };

    t_buffer* buffer_prod = producto_serializar(&prod);
    buffer_prod->offset = 0;
    t_producto* prod_recibido = producto_deserializar(buffer_prod);

    printf("ID: %u\n", prod_recibido->id);
    printf("Precio: %.2f\n", prod_recibido->precio);
    printf("Nombre: %s\n", prod_recibido->nombre);

    free(prod_recibido->nombre);
    free(prod_recibido);
    buffer_destroy(buffer_prod);

    return 0;
}
