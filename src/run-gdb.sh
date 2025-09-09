#!/bin/bash
#run gdb-multiarch with the right parameters with the tea.elf file
echo "Starting GDB with tea.elf..."
echo "In GDB: target remote :1234"
echo "Layout: asm and regs"
gdb-multiarch tea.elf -ex "target remote :1234" -ex "layout asm" -ex "layout regs" -ex "break _start"  -ex "break main"  -ex "break tea_decrypt" -ex "break tea_encript" -ex "break fin"
