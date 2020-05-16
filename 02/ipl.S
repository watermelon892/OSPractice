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
    movw $0, %ax
    movw %ax, %ss
    movw $0x7c00, %sp
    movw %ax, %ds
    movw %ax, %es

    movw $msg, %si

putloop:
    movb (%si), %al
    addw $1, %si
    cmpb $0, %al
    je   fin
    movb $0x0e, %ah
    movw $15, %bx
    int  $0x10
    jmp  putloop

fin:
    hlt
    jmp fin

msg:
    .byte  0x0a, 0x0a
    .ascii "hello, world!"
    .byte  0x0a
    .byte  0
    .org   0x1fe, 0

    .byte  0x55, 0xaa

    .byte  0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
    .skip  4600
    .byte  0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
    .skip  1469432
