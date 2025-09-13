// ============= LICENCIA =============
// MIT License
// Copyright (c) 2025 Alexander Montero Vargas
// Consulta el archivo LICENSE para más detalles.
// =======================================




#include "lib/print.h"
#include "lib/fkcs7p.h"
#include <stdint.h>


extern void tea_encrypt_asm(uint32_t* data, uint32_t* key);
extern void tea_decrypt_asm(uint32_t* data, uint32_t* key);

/*
# Function: demo
# Description:
#   Demostración del cifrado y descifrado TEA en ensamblador RISC-V
#   con padding PKCS7 en C. 
# Params:
#   Ninguno
#
# Returns:
#   Ninguno
#
#
*/

void demo() {

    // Cambie la variable *message* por el mensaje a encripar
    // Cambie el valor de key por un key de 128bits de su preferencia.
    // Vuelva a ejecutar el script ./build.sh
    // Ejecute el script para qemu.
    // Visualice y avance con la ejecución usando el script de GDB.

    char message[] = "Prueba ejemplo TEA C-ASMRV32"; // string en vez de lista hexadecimal
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

/*
# Function: fin
# Description:
#   Función de finalización del programa. 
#   Funciona para colocar un breakpoint en GDB y finalizar el programa de forma segura.
# Params:
#   Ninguno
# Returns:
#   Ninguno
*/
void fin() {
    print_char('\n');
}

/*
# Function: main
# Description:
#   Función principal del programa. Llama a la función demo y finaliza el programa.
# Params:
#   Ninguno
# Returns:
#   0 - Indica que el programa terminó correctamente.
*/

int main() {
    demo(); // Llama a la función demo que contiene la lógica principal
    print_string("Ejecución de programa TEA terminada.\n");
    fin(); // Llama a la función de finalización para detener con GDB
    return 0; // Termina el programa correctamente para GDB
}