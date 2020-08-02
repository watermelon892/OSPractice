    .text
    .code16

    .set VBEMODE, 0x100        // Screen Mode 1024 x 768 x 8bit-color
                               // 0x100 :  640 x  400 8bit-color
                               // 0x101 :  640 x  480 8bit-color
                               // 0x103 :  800 x  600 8bit-color
                               // 0x105 : 1024 x  768 8bit-color
                               // 0x107 : 1280 x 1024 8bit-color

    .set BOTPAK,  0x00280000   // Load destination of bootpack
    .set DSKCAC,  0x00100000   // Place of Disk cache
    .set DSKCAC0, 0x00008000   // Place of Disk cache (Real Mode)

    .set CYLS,    0x0ff0       // Set by boot sector
    .set LEDS,    0x0ff1
    .set VMODE,   0x0ff2       // Information about colors. N bit color?
    .set SCRNX,   0x0ff4       // Display Resolution X
    .set SCRNY,   0x0ff6       // Display Resolution Y
    .set VRAM,    0x0ff8       // Start address of the graphic buffer

    // Confirming the existence of VBE
    movw $0x9000, %ax
    movw %ax, %es
    movw $0x0000, %di
    movw $0x4f00, %ax
    int  $0x10
    cmpw $0x004f, %ax
    jne  scrn320

    // VBE version check
    movw %es:4(%di), %ax
    cmpw $0x0200, %ax
    jb   scrn320

    // Get screen mode information
    movw $VBEMODE, %cx
    movw $0x4f01, %ax
    int  $0x10
    cmpw $0x004f, %ax
    jne  scrn320

    // Confirm screen mode information
    // word  %es:0x00(%di) : Mode attribute. bit7 must be 1.
    // word  %es:0x12(%di) : X resolution
    // word  %es:0x14(%di) : Y resolution
    // byte  %es:0x19(%di) : Number of colors. must be 8.
    // byte  %es:0x1b(%di) : How to specify the color. must be 4(Palette mode)
    // dword %es:0x28(%di) : VRAM address
    cmpb $8, %es:0x19(%di)
    jne  scrn320
    cmpb $4, %es:0x1b(%di)
    jne  scrn320
    movw %es:0x00(%di), %ax
    andw $0x0080, %ax
    jz   scrn320

    // Switch screen mode
    movw $VBEMODE+0x4000, %bx
    movw $0x4f02, %ax
    int  $0x10
    movb $8, (VMODE)           // Save screen mode
    movw %es:0x12(%di), %ax
    movw %ax, (SCRNX)
    movw %es:0x14(%di), %ax
    movw %ax, (SCRNY)
    movl %es:0x28(%di), %eax
    movl %eax, (VRAM)
    jmp  keystatus

// Use 320x200 screen
scrn320:
    movb $0x13, %al            // 320 x 200 x 8bit color
    movb $0x00, %ah
    int  $0x10
    movb $8, (VMODE)
    movw $320, (SCRNX)
    movw $200, (SCRNY)
    movl $0x000a0000, (VRAM)

keystatus:
    // Get keyboard led status from BIOS
    movb $0x02, %ah
    int  $0x16                 // Keyboard BIOS
    movb %al, (LEDS)

    // Prevent PIC from accepting interrupts

    movb $0xff, %al
    outb %al, $0x21
    nop
    outb %al, $0xa1

    cli

    // Setting A20GATE
    // Allow the CPU to access more than 1MB of memory

    call waitkbdout
    movb $0xd1, %al
    outb %al, $0x64
    call waitkbdout
    movb $0xdf, %al            // Enable A20
    outb %al, $0x60
    call waitkbdout

    // Protect Mode

    .arch i486                 // I want to use instructions up to 486

    lgdt (GDTR0)               // Provisionally set GDT
    movl %cr0, %eax
    andl $0x7fffffff, %eax     // Set BIT31 to 0 (To prohibit paging)
    orl  $0x00000001, %eax     // Set BIT0 to 1 (To enter protected mode)
    movl %eax, %cr0
    jmp  pipelineflush

pipelineflush:
    movw $1*8, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    // bootpack transfer
    movl $bootpack, %esi
    movl $BOTPAK, %edi
    movl $512*1024/4, %ecx
    call memcpy

    // Boot Sector
    movl $0x7c00, %esi
    movl $DSKCAC, %edi
    movl $512/4, %ecx
    call memcpy

    movl  $DSKCAC0+512, %esi
    movl  $DSKCAC+512, %edi
    movl  $0, %ecx
    movb  (CYLS), %cl
    imull $512*18*2/4, %ecx
    sub   $512/4, %ecx
    call  memcpy

    // Boot Pack Startup

    movl $BOTPAK, %ebx
    movl 16(%ebx), %ecx
    add  $3, %ecx
    shr  $2, %ecx
    jz   skip
    movl 20(%ebx), %esi
    add  %ebx, %esi
    movl 12(%ebx), %edi
    call memcpy

skip:
    mov   12(%ebx), %esp
    ljmpl $2*8, $0x0000001b

waitkbdout:
    inb  $0x64, %al
    andb $0x02, %al
    inb  $0x60, %al
    jnz  waitkbdout
    ret

memcpy:
    movl (%esi), %eax
    add  $4, %esi
    movl %eax, (%edi)
    add  $4, %edi
    sub  $1, %ecx
    jnz  memcpy
    ret

    .align 16
GDT0:
    .skip 8, 0x00
    .word 0xffff, 0x0000, 0x9200, 0x00cf
    .word 0xffff, 0x0000, 0x9a28, 0x0047
    .word 0x0000

GDTR0:
    .word 8*3-1
    .int  GDT0

bootpack:
