# Funcion ensamblador para encriptar 64bits con una clave de 128bits
# Function signature: void tea_encript()
# a0 = input parameter n
# a0 = return value

.section .text
.globl tea_encript

tea_encript:

    lw      t0, 0(a0)          # t0 = v0
    lw      t1, 4(a0)          # t1 = v1

    lw      a2, 8(a1)          # a2 = kEY[0]
    lw      a3, 12(a1)         # a3 = KEY[1]
    lw      a4, 16(a1)         # a4 = KEY[2]
    lw      a5, 20(a1)         # a5 = KEY[3]

    # carga constantes
    li      a6, 0x9e3779b9      # a6 = delta
    li      a7, 32              # a7 = rondas
    li      t2, 0               # t2 = sum = 0

loop_encrypt:
    beq a7, zero, end_encrypt  # if (rounds == 0) end_encrypt
    
    add t2, t2, a6          # sum += delta
    
    # V0
    slli t4, t1, 4      # (v1 << 4)
    add t4, t4, a2      # (v1 << 4) + kEY[0]

    add t5, t1, t2     # v1 + sum
    xor t4, t4, t5     # ((v1 << 4) + kEY[0]) ^ (v1 + sum)

    srai t5, t1, 5     # (v1 >> 5)
    add t5, t5, a4     # (v1 >> 5)  + kEY[1]

    xor t4, t4, t5     # (((v1 << 4) + kEY[0]) ^ (v1 + sum)) ^ ((v1 >> 5)  + kEY[1])
    add t0, t0, t4     # v0 += ...

    # V1
    slli t4, t0, 4      # (v0 << 4)
    add t4, t4, a4      # (v0 << 4) + kEY[2]
    
    add t5, t0, t2      # v0 + sum
    xor t4, t4, t5      # ((v0 << 4) + kEY[2]) ^ (v0 + sum)
    
    srai t5, t0, 5      # (v0 >> 5)
    add t5, t5, a5      # (v0 >> 5) + kEY[3]
    
    xor t4, t4, t5      # (((v0 << 4) + kEY[2]) ^ (v0 + sum)) ^ ((v0 >> 5)  + kEY[3])
    add t1, t1, t4      # v1 += ...


    addi a7, a7, -1     # rounds--
    j loop_encrypt

end_encrypt:
    sw t0, 0(a0)          # store v0
    sw t1, 4(a0)          # store v1
    ret
