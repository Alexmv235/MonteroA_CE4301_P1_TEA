#!/bin/bash

# Build script for C+assembly tea
echo "Building C+assembly tea..."

# Compile C source to object file
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 \
    -gdwarf-4 \
    -c \
    source/tea.c \
    -o  source/out/tea.o

if [ $? -ne 0 ]; then
    echo "C compilation failed"
    exit 1
fi

# Compile startup assembly to object file
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 \
    -gdwarf-4 \
    -c \
    source/startup.s \
    -o  source/out/startup.o

if [ $? -ne 0 ]; then
    echo "Startup assembly compilation failed"
    exit 1
fi

# Compile tea_enc assembly source to object file
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 \
    -gdwarf-4 \
    -c \
    source/lib/tea_enc.s \
    -o  source/out/tea_enc.o

if [ $? -ne 0 ]; then
    echo "tea_enc assembly compilation failed"
    exit 1
fi

# Compile tea_dec assembly source to object file
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 \
    -gdwarf-4 \
    -c \
    source/lib/tea_dec.s \
    -o  source/out/tea_dec.o

if [ $? -ne 0 ]; then
    echo "tea_dec assembly compilation failed"
    exit 1
fi

# Compile print.c to object file
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 \
    -gdwarf-4 \
    -c \
    source/lib/print.c \
    -o  source/out/print.o

if [ $? -ne 0 ]; then
    echo "print.c compilation failed"
    exit 1
fi


# Compile fkcs7p.c to object file
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 \
    -gdwarf-4 \
    -c \
    source/lib/fkcs7p.c \
    -o  source/out/fkcs7p.o

if [ $? -ne 0 ]; then
    echo "print.c compilation failed"
    exit 1
fi

# Link object files together
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 \
    -gdwarf-4 \
     source/out/startup.o \
     source/out/tea.o \
     source/out/print.o \
     source/out/fkcs7p.o \
     source/out/tea_enc.o \
     source/out/tea_dec.o \
    -T source/linker.ld \
    -o tea.elf

if [ $? -eq 0 ]; then
    echo "Build successful: tea.elf created"
    echo "Object files: tea.o,    
    tea_enc.o, tea_dec.o"
else
    echo "Linking failed"
    exit 1
fi