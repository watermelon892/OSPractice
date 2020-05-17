    .text
    .code16

    movb $0x13, %al   // VGA graphics. 320x200x8bit Color
    movb $0x00, %ah
    int  $0x10

fin:
    hlt
    jmp fin
