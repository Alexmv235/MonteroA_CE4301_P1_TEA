# 1. Descripción de la Arquitectura del Software

La arquitectura del proyecto se diseñó con una **separación clara entre las capas escritas en C y en ensamblador (ASM RV32)**, con el objetivo de garantizar legibilidad, modularidad y eficiencia en las operaciones críticas.  

## 1.1 Separación entre capas C y ensamblador

- **C (alto nivel):**  
  Se encarga de la gestión general de datos y de la interacción con el usuario. Aquí se implementan las funciones relacionadas con:
  - Manipulación de cadenas de texto (entrada y salida).
  - Procesamiento de la clave de 128 bits utilizada para el cifrado.
  - Aplicación de padding a la cadena de texto, asegurando la normalización del tamaño antes de encriptar.
  - Simulación de comunicación UART hacia la consola, empleada para la impresión de cadenas y caracteres.

- **Ensamblador RV32 (bajo nivel):**  
  Implementa las rutinas críticas de cifrado/descifrado mediante el algoritmo TEA (Tiny Encryption Algorithm). Al estar escrito directamente en ASM:
  - Se optimiza el uso de registros y operaciones aritméticas.  
  - Se asegura un mejor control sobre la manipulación de datos en memoria.  
  - Se aprovechan las instrucciones específicas de la arquitectura RISC-V para maximizar el rendimiento.
- **Conexión entre ambos niveles:**
Lo interconexión entre ambas capas de realiza en tiempo de compilación del proyecto C, donde mediante un *linker* se integran las funciones de ASM con el codigo compilado en C en un único ejecutable.

## 1.2 Interfaces utilizadas

La interacción entre las capas C y ensamblador se realiza mediante **funciones externas declaradas en C y definidas en ASM**.  
Este mecanismo permite que la lógica de alto nivel invoque directamente las operaciones críticas de cifrado sin perder control ni eficiencia.

En este caso, por ejemplo para la función "tea_encrypt_asm" se realizó la siguiente declaración externa en C:

```c
// Declaración en C
extern void tea_encrypt_asm(uint32_t* data, uint32_t* key);
```
Mientras que la función se definió en código ensamblador de la siguiente manera:

```asm
.globl tea_encrypt_asm
tea_encrypt_asm:
    # IMPLEMTENTACIÓN ...
```
De esta forma:

El código en C prepara los datos y gestiona la memoria.

El ensamblador se encarga de procesarlos con las rutinas de bajo nivel.

## 1.3 Justificación de las decisiones de diseño

Modularidad: Separar la lógica de alto nivel (C) de las rutinas de cifrado (ASM) facilita la comprensión, depuración y futura ampliación del proyecto.

Eficiencia: El cifrado requiere operaciones repetitivas y bit a bit, que se ejecutan de forma más eficiente en ensamblador optimizado.

Portabilidad: Al mantener la gestión de cadenas y la lógica general en C, el código puede adaptarse fácilmente a otros entornos o arquitecturas.

Simulación realista: La emulación de UART en C permite verificar el comportamiento del sistema de salida sin necesidad de hardware físico adicional.
