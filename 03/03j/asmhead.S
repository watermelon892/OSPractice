    .text
    .code16

    .set BOTPAK, 0x00280000    // Load destination of bootpack
    .set DSKCAC, 0x00100000    // Place of Disk cache
    .set DSKCAC0, 0x00008000   // Place of Disk cache (Real Mode)

    .set CYLS, 0x0ff0          // Set by boot sector
    .set LEDS, 0x0ff1
    .set VMODE, 0x0ff2         // Information about colors. N bit color?
    .set SCRNX, 0x0ff4         // Display Resolution X
    .set SCRNY, 0x0ff6         // Display Resolution Y
    .set VRAM, 0x0ff8          // Start address of the graphic buffer

    // Setting Video Mode
    movb $0x13, %al            // VGA graphics. 320x200x8bit Color
    movb $0x00, %ah
    int  $0x10

    movb $8, (VMODE)           // Save screen mode
    movw $320, (SCRNX)
    movw $200, (SCRNY)
    movl $0x000a0000, (VRAM)

    // Get keyboard led status from BIOS
    mov  $0x02, %ah
    int  $0x16                 // Keyboard BIOS
    mov  %al, (LEDS)

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
    SHR  $2, %ecx
    jz   skip
    movl 20(%ebx), %esi
    add  %ebx, %esi
    movl 12(%ebx), %edi
    call memcpy

skip:
    mov   12(%ebx), %esp
    ljmpl $2+8, $0x0000001b

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

    .align 16
bootpack:
