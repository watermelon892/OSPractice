    /*
    | nasm (nask) |  GAS        |
    +-------------+-------------+
    | DB          | .byte       |
    | DW          | .word       |
    | DD          | .int        |
    | ORG         | -           |
    | fresb       | .org        |
    +-------------+-------------+
    | JMP         | jmp         |
    | MOV         | movw / movb |
    | ADD         | addw        |
    | CMP         | cmpb        |
    | JE          | je          |
    | INT         | int         |
    | HLT         | hlt         |
    */

    .code16 // Output 16-bit code on x86

    jmp    entry
    .byte  0x90
    .ascii "HELLOIPL"
    .word  512
    .byte  1
    .word  1
    .byte  2
    .word  224
    .word  2880
    .byte  0xf0
    .word  9
    .word  18
    .word  2
    .int   0
    .int   2880
    .byte  0, 0, 0x29
    .int   0xffffffff
    .ascii "HELLO-OS   "
    .ascii "FAT12   "
    .skip  18, 0

entry:
    // Init Registers
    movw $0, %ax
    movw %ax, %ss
    movw $0x7c00, %sp
    movw %ax, %ds

    // Load Disk
    movw $0x0820, %ax
    movw %ax, %es
    movb $0, %ch     // Cylinder: 0
    movb $0, %dh     // Head: 0
    movb $2, %cl     // Sector: 2

    movb $0x02, %ah  // AH=0x02 Read Disk
    movb $1, %al     // 1 Sector
    movw $0, %bx
    movb $0x00, %dl  // A Drive
    int  $0x13       // Call Disk Bios
    jc   error

fin:
    // Sleep
    hlt
    jmp fin

error:
    movw $msg, %si

putloop:
    movb (%si), %al
    addw $1, %si     // Add 1 to SI
    cmpb $0, %al
    je   fin
    movb $0x0e, %ah  // 1 character display function
    movw $15, %bx    // Color code
    int  $0x10       // Call Video Bios
    jmp  putloop

msg:
    .byte  0x0a, 0x0a
    .ascii "load error"
    .byte  0x0a
    .byte  0

    .org   0x1fe, 0

    .byte  0x55, 0xaa
