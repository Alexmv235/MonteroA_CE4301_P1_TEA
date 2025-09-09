#!/bin/bash
#run gdb-multiarch with the right parameters with the tea.elf file
echo "Starting GDB with tea.elf..."
echo "In GDB: target remote :1234"
echo "Layout: asm and regs"
gdb-multiarch tea.elf -x debug.gdb
