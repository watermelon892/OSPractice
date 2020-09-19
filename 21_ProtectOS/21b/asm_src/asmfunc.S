    .arch i486

    .text

    // Function name included in this program
    .global io_hlt, io_cli, io_sti, io_stihlt
    .global io_in8, io_in16, io_in32
    .global io_out8, io_out16, io_out32
    .global io_load_eflags, io_store_eflags
    .global load_gdtr, load_idtr
    .global load_cr0, store_cr0
    .global load_tr
    .global asm_inthandler20, asm_inthandler21
    .global asm_inthandler27, asm_inthandler2c
    .global memtest_sub
    .global farjmp, farcall
    .global asm_hrb_api

    .extern inthandler20, inthandler21
    .extern inthandler27, inthandler2c
    .extern hrb_api

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
    movw 4(%esp), %ax  // limit
    movw %ax, 6(%esp)
    lgdt 6(%esp)
    ret

// void load_idtr(int limit, int addr)
load_idtr:
    movw 4(%esp), %ax  // limit
    movw %ax, 6(%esp)
    lidt 6(%esp)
    ret

// int load_cr0(void)
load_cr0:
    movl %cr0, %eax
    ret

// void store_cr0(int cr0)
store_cr0:
    movl 4(%esp), %eax
    movl %eax, %cr0
    ret

// void load_tr(int tr)
load_tr:
    ltr 4(%esp)
    ret

// void asm_inthandler20(void)
asm_inthandler20:
    push %es
    push %ds
    pusha
    movl %esp, %eax
    push %eax
    movw %ss, %ax
    movw %ax, %ds
    movw %ax, %es
    call inthandler20
    pop  %eax
    popa
    pop  %ds
    pop  %es
    iret

// void asm_inthandler21(void)
asm_inthandler21:
    push %es
    push %ds
    pusha
    movl %esp, %eax
    push %eax
    movw %ss, %ax
    movw %ax, %ds
    movw %ax, %es
    call inthandler21
    pop  %eax
    popa
    pop  %ds
    pop  %es
    iret

// void asm_inthandler27(void)
asm_inthandler27:
    push %es
    push %ds
    pusha
    movl %esp, %eax
    push %eax
    movw %ss, %ax
    movw %ax, %ds
    movw %ax, %es
    call inthandler27
    pop  %eax
    popa
    pop  %ds
    pop  %es
    iret

// void asm_inthandler2c(void)
asm_inthandler2c:
    push %es
    push %ds
    pusha
    movl %esp, %eax
    push %eax
    movw %ss, %ax
    movw %ax, %ds
    movw %ax, %es
    call inthandler2c
    pop  %eax
    popa
    pop  %ds
    pop  %es
    iret

// unsigned int memtest_sub(unsigned int start, unsigned int end)
memtest_sub:
    push %edi // I also want to use EBX, ESI, and EDI
    push %esi
    push %ebx
    movl $0xaa55aa55, %esi   // pat0 = 0xaa55aa55
    movl $0x55aa55aa, %edi   // pat1 = 0x55aa55aa
    movl 12 + 4(%esp), %eax  // i = start
mts_loop:
    movl %eax, %ebx
    addl $0xffc, %ebx        // p = i + 0xffc
    movl (%ebx), %edx        // old = *p
    movl %esi, (%ebx)        // *p = pat0
    xorl $0xffffffff, (%ebx) // *p ^= 0xffffffff
    cmpl (%ebx), %edi        // if (*p == pat1) goto mts_fin
    jne  mts_fin
    xorl $0xffffffff, (%ebx) // *p ^= 0xffffffff
    cmpl (%ebx), %esi        // if (*p != pat0) goto mts_fin
    jne  mts_fin
    movl %edx, (%ebx)        // *p = old
    addl $0x1000, %eax       // i += 0x1000
    cmpl 12 + 8(%esp), %eax  // if (i <= end) goto mts_loop
    jbe  mts_loop
    pop  %ebx
    pop  %esi
    pop  %edi
    ret
mts_fin:
    movl %edx, (%ebx)        // *p = old
    pop  %ebx
    pop  %esi
    pop  %edi
    ret

// void farjmp(int eip, int cs)
farjmp:
    ljmp *4(%esp)
    ret

// void farcall(int eip, int cs)
farcall:
    lcall 4(%esp)
    ret

// void asm_hrb_api(void)
asm_hrb_api:
    sti
    pusha
    pusha
    call hrb_api
    addl $32, %esp
    popa
    iret
