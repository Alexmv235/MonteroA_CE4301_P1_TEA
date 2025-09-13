// ============= LICENCIA =============
// MIT License
// Copyright (c) 2025 Alexander Montero Vargas
// Consulta el archivo LICENSE para más detalles.
// =======================================

#ifndef FKCS7P_H
#define FKCS7P_H
#include <stdint.h>

int fkcs7_pad(const uint8_t* input, int input_len, uint8_t* output);
int fkcs7_unpad(uint8_t* buf, int buf_len);

#endif // FKCS7P_H
