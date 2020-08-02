    .arch i486

    .text

    // Function name included in this program
    .global io_hlt
    .global write_mem8

// void _io_hlt(void)
io_hlt:
    hlt
    ret

// void _write_mem8(int addr, int data)
write_mem8:
    movl 4(%esp), %ecx
    movb 8(%esp), %al
    mov  %al, (%ecx)
    ret
