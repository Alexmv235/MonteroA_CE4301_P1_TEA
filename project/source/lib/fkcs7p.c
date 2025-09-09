#include "fkcs7p.h"
#include <stdint.h>

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
