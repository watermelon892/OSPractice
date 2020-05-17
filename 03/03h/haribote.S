    .text
    .code16

    .set CYLS, 0x0ff0   // Set by boot sector
    .set LEDS, 0x0ff1
    .set VMODE, 0x0ff2  // Information about colors. N bit color?
    .set SCRNX, 0x0ff4  // Display Resolution X
    .set SCRNY, 0x0ff6  // Display Resolution Y
    .set VRAM, 0x0ff8   // Start address of the graphic buffer

    movb $0x13, %al     // VGA graphics. 320x200x8bit Color
    movb $0x00, %ah
    int  $0x10

    movb $8, (VMODE)    // Save screen mode
    movw $320, (SCRNX)
    movw $200, (SCRNY)
    movl $0x000a0000, (VRAM)

    // Get keyboard led status from BIOS
    mov  $0x02, %ah
    int  $0x16         // Keyboard BIOS
    mov  %al, (LEDS)

fin:
    hlt
    jmp fin
