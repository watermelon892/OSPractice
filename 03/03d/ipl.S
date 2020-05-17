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
    | ADD         | add  / addw |
    | CMP         | cmpw / cmpb |
    | JE          | je          |
    | JNC         | jnc         |
    | JAE         | jae         |
    | JB          | jb          |
    | JBE         | jbe         |
    | INT         | int         |
    | HLT         | hlt         |
    */

    .code16 // Output 16-bit code on x86
    .set CYLS, 10

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

readloop:
    movw $0, %si     // Register that counts the number of failures

retry:
    movb $0x02, %ah  // AH=0x02 Read Disk
    movb $1, %al     // 1 Sector
    movw $0, %bx
    movb $0x00, %dl  // A Drive
    int  $0x13       // Call Disk Bios
    jnc  next
    addw $1, %si     // Add 1 to SI
    cmpw $5, %si     // Compare SI and 5
    jae  error       // IF SI >= 5 THEN error
    movb $0x00, %ah
    movb $0x00, %dl  // A Drive
    int  $0x13       // Reset Drive
    jmp  retry

next:
    movw %es, %ax     // Advance address by 0x200
    add  $0x0020, %ax // ES * 16 + BX = 0x0020, 512 Byte, 1 Sector
    movw %ax, %es     // Because 'add 0x020 %es' not exist.
    add  $1, %cl      // Add 1 to CL
    cmp  $18, %cl     // Compare CL and 18
    jbe  readloop     // IF CL <= 18 THEN readloop

    movb $1, %cl      // Reset sector
    addb $1, %dh      // Next head
    cmp  $2, %dh      // Compare DH and 2
    jb   readloop     // IF DH < 2 THEN readloop

    movb $0, %dh      // Rest head
    addb $1, %ch      // Read to Cylinder CYLS
    cmp  $CYLS, %ch   // Compare CH and CYLS
    jb   readloop     // IF CH < CYLS THEN readloop

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
