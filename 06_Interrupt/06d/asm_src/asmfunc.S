    .arch i486

    .text

    // Function name included in this program
    .global io_hlt, io_cli, io_sti, io_stihlt
    .global io_in8, io_in16, io_in32
    .global io_out8, io_out16, io_out32
    .global io_load_eflags, io_store_eflags
    .global load_gdtr, load_idtr

// void _io_hlt(void)
io_hlt:
    hlt
    ret

// void io_cli(void)
io_cli:
    cli
    ret

// void io_sti(void)
io_sti:
    sti
    ret

// void io_stihlt(void)
io_stihlt:
    sti
    hlt
    ret

// int io_in8(int port)
io_in8:
    movl 4(%esp), %edx  // port
    movl $0, %eax
    inb  %dx, %al
    ret

// int io_in16(int port)
io_in16:
    movl 4(%esp), %edx  // port
    movl $0, %eax
    inw  %dx, %ax
    ret

// int io_int32(int port)
io_in32:
    movl 4(%esp), %edx  // port
    inl  %dx, %eax
    ret

// int io_out8(int port, int data)
io_out8:
    movl 4(%esp), %edx  // port
    movb 8(%esp), %al   // data
    outb %al, %dx
    ret

// int io_out16(int port, int data)
in_out16:
    movl 4(%esp), %edx  // port
    movl 8(%esp), %eax  // data
    outw %ax, %dx
    ret

// int io_out32(int port, int data)
in_out32:
    movl 4(%esp), %edx  // port
    movl 8(%esp), %eax  // data
    outl %eax, %dx
    ret

// int io_load_eflags(void)
io_load_eflags:
    pushf  // PUSH EFLAGS
    pop %eax
    ret

// int io_store_eflags(int eflags)
io_store_eflags:
    movl 4(%esp), %eax
    push %eax
    popf   // POP EFLAGS
    ret

// void load_gdtr(int limit, int addr)
load_gdtr:
    mov  4(%esp), %ax  // limit
    mov  %ax, 6(%esp)
    lgdt 6(%esp)
    ret

// void load_idtr(int limit, int addr)
load_idtr:
    mov  4(%esp), %ax  // limit
    mov  %ax, 6(%esp)
    lidt 6(%esp)
    ret
