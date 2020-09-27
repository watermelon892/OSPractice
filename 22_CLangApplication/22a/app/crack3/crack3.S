    .arch i486

    // io_out8(PIT_CTRL, 0x34)
    movb $0x34, %al
    outb %al, $0x43

    // io_out8(PIT_CNT0, 0xff)
    movb $0xff, %al
    outb %al, $0x40

    // io_out8(PIT_CNT0, 0xff)
    movb $0xff, %al
    outb %al, $0x40

    mov  $4, %edx
    int  $0x40
