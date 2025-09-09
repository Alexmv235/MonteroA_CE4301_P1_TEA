#include <stdint.h>

// Simple C program that calls assembly function
// This demonstrates C+assembly integration in RISC-V

// Assembly function declaration
extern int sum_to_n(int n);
extern void tea_encrypt(uint32_t* data, uint32_t* key);
extern void tea_decrypt(uint32_t* data, uint32_t* key);

// ==========================
// Bare-metal UART printing
// ==========================

void print_char(char c) {
    volatile char *uart = (volatile char*)0x10000000;
    *uart = c;
}

void print_string(const char* str) {
    while (*str) {
        print_char(*str++);
    }
}

// Hex printer
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

// Array ASCII printer
void print_array_ascii(const uint8_t* buf, int len) {
    for (int i = 0; i < len; i++) {
        print_char((char)buf[i]);
    }
}

// ==========================
// FKCS7 padding/unpadding
// ==========================

int fkcs7_pad(const uint8_t* input, int input_len, uint8_t* output) {
    int pad_len = 8 - (input_len % 8);
    if (pad_len == 0) pad_len = 8;

    // Copy input
    for (int i = 0; i < input_len; i++)
        output[i] = input[i];

    // Add padding
    for (int i = 0; i < pad_len; i++)
        output[input_len + i] = (uint8_t)pad_len;

    return input_len + pad_len; // total length after padding
}

int fkcs7_unpad(uint8_t* buf, int buf_len) {
    if (buf_len == 0) return 0;

    uint8_t pad_len = buf[buf_len - 1];
    if (pad_len == 0 || pad_len > 8) return 0; // invalid padding

    for (int i = 0; i < pad_len; i++) {
        if (buf[buf_len - 1 - i] != pad_len)
            return 0; // invalid padding
    }

    return buf_len - pad_len; // length after removing padding
}

// ==========================
// Demo
// ==========================

void demo() {
    char message[] = "ESCUELA DE INGENIERIA EN COMPUTADORES"; // string en vez de lista hexadecimal
    int message_len = sizeof(message) - 1; // no cuenta el null terminator
    uint8_t buffer[message_len + 8]; // tamaño suficiente para padding

    // 128 bits key  0x12345678u, 0x9ABCDEF0u, 0xFEDCBA98u, 0x76543210u
    uint32_t key[4] = {0x12345678u, 0x9ABCDEF0u, 0xFEDCBA98u, 0x76543210u};



    


    // 3️⃣ Print unpadded as ASCII
    print_string("Unpadded buffer (ASCII):\t");
    print_array_ascii(message, message_len);
    print_string("\n");


    // 1️⃣ Pad
    int padded_len = fkcs7_pad((uint8_t*)message, message_len, buffer);
    print_string("Padded buffer (hex):\t");
    print_buffer_hex(buffer, padded_len);
    print_string("\n");

    // 4️⃣ Call assembly function
    // tamaño se registros de 32 bits
    int tam = padded_len / 8; // número de registros de 32 bits
    for (int i = 0; i < tam; i++) {
        //funcion esamblador foo que recibe buffer + i*8 y key
        tea_encrypt((uint32_t*)(buffer + i * 8), key);
    }
    //cadena encriptada
    print_string("Encrypted buffer (hex):\t");
    print_buffer_hex(buffer, padded_len);
    print_string("\n");

    // 5️⃣ Decrypt
    for (int i = 0; i < tam; i++) {
        //funcion esamblador foo que recibe buffer + i*8 y key
        tea_decrypt((uint32_t*)(buffer + i * 8), key);
    }
    print_string("Decrypted buffer (hex):\t");
    print_buffer_hex(buffer, padded_len);
    print_string("\n");

    // 2️⃣ Unpad
    int unpadded_len = fkcs7_unpad(buffer, padded_len);
    // unpadder buffer
    print_string("Unpadded buffer (hex):\t");
    print_buffer_hex(buffer, unpadded_len);
    print_string("\n");

    // 3️⃣ Print unpadded as ASCII
    print_string("Unpadded and decripted buffer (ASCII):\t");
    print_array_ascii(buffer, unpadded_len);
    print_string("\n");
}

void fin() {
    print_char('\n');
}

int main() {
    demo();
    print_string("Ejecución de programa TEA terminada.\n");
    fin();
    return 0; // Termina el programa correctamente para GDB
}