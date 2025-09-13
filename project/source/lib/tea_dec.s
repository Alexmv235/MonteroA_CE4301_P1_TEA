# ============= LICENCIA =============
# MIT License
# Copyright (c) 2025 Alexander Montero Vargas
# Consulta el archivo LICENSE para más detalles.
# =======================================

.section .text
.globl tea_decrypt_asm

# Function: tea_decrypt_asm
# Description:
#               Desencripta un bloque de 64 bits usando una clave de 128 bits (TEA)
# Params:
#   a0: dirección del bloque de datos de 64 bits (v0 | v1)
#   a1: dirección de la clave de 128 bits (KEY[0..3])
#
# Returns:
#   El bloque desencriptado se almacena en la misma dirección a0
#
# Registros usados: t0, t1, t2, t3, t4, t5, a2, a3, a4, a5, a6
#
#References:
#   - David J Wheeler and Roger M Needham. Tea, a tiny encryption algorithm
#       https://www.tayloredge.com/reference/Mathematics/TEA-XTEA.pdf


tea_decrypt_asm:

    lw      t0, 0(a0)          # t0 = v0
    lw      t1, 4(a0)          # t1 = v1

    lw      a2, 8(a1)          # a2 = kEY[0]
    lw      a3, 12(a1)         # a3 = KEY[1]
    lw      a4, 16(a1)         # a4 = KEY[2]
    lw      a5, 20(a1)         # a5 = KEY[3]

    # carga constantes
    li      a6, 0x9e3779b9      # a6 = delta
    li      t2, 0xC6EF3720     # sum = delta * 32
    li      t3, 32              # t3 = rondas

loop_decrypt:
    beq t3, zero, end_decrypt  # if (rondas == 0) end_decrypt
    
    # V1
    slli t4, t0, 4      # (v0 << 4)
    add t4, t4, a4      # (v0 << 4) + kEY[2]
    
    add t5, t0, t2      # v0 + sum
    xor t4, t4, t5      # ((v0 << 4) + kEY[2]) ^ (v0 + sum)
    
    srai t5, t0, 5      # (v0 >> 5)
    add t5, t5, a5      # (v0 >> 5) + kEY[3]
    
    xor t4, t4, t5      # (((v0 << 4) + kEY[2]) ^ (v0 + sum)) ^ ((v0 >> 5)  + kEY[3])
    sub t1, t1, t4      # v1 -= ...

    # V0
    slli t4, t1, 4      # (v1 << 4)
    add t4, t4, a2      # (v1 << 4) + kEY[0]

    add t5, t1, t2     # v1 + sum
    xor t4, t4, t5     # ((v1 << 4) + kEY[0]) ^ (v1 + sum)

    srai t5, t1, 5     # (v1 >> 5)
    add t5, t5, a4     # (v1 >> 5)  + kEY[1]

    xor t4, t4, t5     # (((v1 << 4) + kEY[0]) ^ (v1 + sum)) ^ ((v1 >> 5)  + kEY[1])
    sub t0, t0, t4     # v0 -= ...

    sub t2, t2, a6      # sum -= delta

    addi t3, t3, -1     # rondas--
    j loop_decrypt

end_decrypt:
    sw t0, 0(a0)          # store v0
    sw t1, 4(a0)          # store v1
    ret
