#include "print.h"

void print_char(char c) {
    volatile char *uart = (volatile char*)0x10000000;
    *uart = c;
}

void print_string(const char* str) {
    while (*str) {
        print_char(*str++);
    }
}

char nibble_to_hex(uint8_t nibble) {
    return (nibble < 10) ? ('0' + nibble) : ('A' + (nibble - 10));
}

void print_byte_hex(uint8_t byte) {
    print_char(nibble_to_hex((byte >> 4) & 0x0F));
    print_char(nibble_to_hex(byte & 0x0F));
}

void print_buffer_hex(const uint8_t* buf, int len) {
    for (int i = 0; i < len; i++) {
        print_byte_hex(buf[i]);
        print_char(' ');
    }
}

void print_array_ascii(const uint8_t* buf, int len) {
    for (int i = 0; i < len; i++) {
        print_char((char)buf[i]);
    }
}
