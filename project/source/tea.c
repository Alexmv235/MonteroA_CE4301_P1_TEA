#include "lib/print.h"
#include "lib/fkcs7p.h"
#include <stdint.h>

// Simple C program that calls assembly function
// This demonstrates C+assembly integration in RISC-V

extern void tea_encrypt_asm(uint32_t* data, uint32_t* key);
extern void tea_decrypt_asm(uint32_t* data, uint32_t* key);

// ==========================
// Demo
// ==========================

void demo() {
    char message[] = "Mensaje de prueba para TEA"; // string en vez de lista hexadecimal
    int message_len = sizeof(message) - 1; // no cuenta el null terminator
    uint8_t buffer[message_len + 8]; // tamaño suficiente para padding

    // 128 bits key  0x9f2b3c4d 0xa1b2c3d4 0x5e6f7788 0x0a1b2c3d
    uint32_t key[4]= {0x9f2b3c4u, 0xa1b2c3d4u, 0x5e6f7788u, 0x0a1b2c3du};

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
        tea_encrypt_asm((uint32_t*)(buffer + i * 8), key);
    }
    //cadena encriptada
    print_string("Encrypted buffer (hex):\t");
    print_buffer_hex(buffer, padded_len);
    print_string("\n");

    // 5️⃣ Decrypt
    for (int i = 0; i < tam; i++) {
        //funcion esamblador foo que recibe buffer + i*8 y key
        tea_decrypt_asm((uint32_t*)(buffer + i * 8), key);
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