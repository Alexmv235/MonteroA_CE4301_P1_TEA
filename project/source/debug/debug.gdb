set confirm off
target remote :1234
layout asm
layout regs
break _start
break main
break tea_decrypt_asm
break tea_encrypt_asm
break fin
commands $bpnum
    kill
    echo \n--- Programa terminado,en pausa dentro de GDB ---\n
    echo - Para volver a conectar con la instancia de qemu\n
    echo - Vuelva a ejecutar ./run-qemu.sh en la otra terminal\n
    echo - Y escriba aqui: (gdb) target remote :1234 \n
    echo - O escriba q y presione enter para salir de GDB\n
    step
end