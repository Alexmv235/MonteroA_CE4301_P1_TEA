// ============= LICENCIA =============
// MIT License
// Copyright (c) 2025 Alexander Montero Vargas
// Consulta el archivo LICENSE para más detalles.
// =======================================

#include "print.h"



/*
// NOTA ACLARATORIA:
Las funciones de imprimir fueron empleas
de forma igual, extendida y/o modificada del
código original propcionado por el profesor
*/


/*
Function: print_char
Description:
   Envía un carácter al UART para impresión.
Params:
   c - Carácter a imprimir.
Returns:
   Ninguno.
References:
   Tomado directamente del código proporcionado por el profesor.
   https://gitlab.com/jgonzalez.tec/rvqemu/-/blob/39261fb70b0ff462850ad8e50d945d1f35ebd424/examples/c-asm/example.c
*/
void print_char(char c) {
    volatile char *uart = (volatile char*)0x10000000;
    *uart = c;
}

/*Function: print_string
Description:
   Envía una cadena de caracteres al UART para impresión.
Params:
   str - Puntero a la cadena de caracteres a imprimir.
Returns:
   Ninguno.
References:
   Tomado directamente del código proporcionado por el profesor.
    https://gitlab.com/jgonzalez.tec/rvqemu/-/blob/39261fb70b0ff462850ad8e50d945d1f35ebd424/examples/c-asm/example.c
*/

void print_string(const char* str) {
    while (*str) {
        print_char(*str++);
    }
}

/*
Function: nibble_to_hex
Description:
   Convierte un nibble (4 bits) a su representación hexadecimal.
Params:
   nibble - Valor del nibble (0-15).
Returns:
   Carácter hexadecimal correspondiente.
References: 
    https://stackoverflow.com/questions/3110306/reading-writing-nibbles-without-bit-fields-in-c-c
    Realizado con ayuda de herramientas de intelligencia artificial.
*/
char nibble_to_hex(uint8_t nibble) {
    return (nibble < 10) ? ('0' + nibble) : ('A' + (nibble - 10));
}

/*Function: print_byte_hex
Description:
   Imprime un byte en formato hexadecimal.
Params:
   byte - Byte a imprimir.
Returns:
   Ninguno.
References: 
    https://stackoverflow.com/questions/3110306/reading-writing-nibbles-without-bit-fields-in-c-c
    Realizado con ayuda de herramientas de intelligencia artificial.
*/
void print_byte_hex(uint8_t byte) {
    print_char(nibble_to_hex((byte >> 4) & 0x0F));
    print_char(nibble_to_hex(byte & 0x0F));
}

/*Function: print_buffer_hex
Description:
   Imprime un buffer de bytes en formato hexadecimal.
Params:
   buf - Puntero al buffer de bytes.
   len - Longitud del buffer.
Returns:
   Ninguno.
*/

void print_buffer_hex(const uint8_t* buf, int len) {
    for (int i = 0; i < len; i++) {
        print_byte_hex(buf[i]);
        print_char(' ');
    }
}

/*Function: print_array_ascii
Description:
   Imprime un array de bytes como caracteres ASCII.
Params:
   buf - Puntero al array de bytes.
   len - Longitud del array.
Returns:
   Ninguno.
*/

void print_array_ascii(const uint8_t* buf, int len) {
    for (int i = 0; i < len; i++) {
        print_char((char)buf[i]);
    }
}
