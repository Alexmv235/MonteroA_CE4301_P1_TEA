// ============= LICENCIA =============
// MIT License
// Copyright (c) 2025 Alexander Montero Vargas
// Consulta el archivo LICENSE para más detalles.
// =======================================

#ifndef PRINT_H
#define PRINT_H
#include <stdint.h>

void print_char(char c);
void print_string(const char* str);
char nibble_to_hex(uint8_t nibble);
void print_byte_hex(uint8_t byte);
void print_buffer_hex(const uint8_t* buf, int len);
void print_array_ascii(const uint8_t* buf, int len);

#endif // PRINT_H
