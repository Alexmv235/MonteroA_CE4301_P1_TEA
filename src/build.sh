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
    tea.c \
    -o tea.o

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
    startup.s \
    -o startup.o

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
    tea_enc.s \
    -o tea_enc.o

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
    tea_dec.s \
    -o tea_dec.o

if [ $? -ne 0 ]; then
    echo "tea_dec assembly compilation failed"
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
    startup.o \
    tea.o \
    tea_enc.o \
    tea_dec.o \
    -T linker.ld \
    -o tea.elf

if [ $? -eq 0 ]; then
    echo "Build successful: tea.elf created"
    echo "Object files: tea.o,    
    tea_enc.o, tea_dec.o"
else
    echo "Linking failed"
    exit 1
fi