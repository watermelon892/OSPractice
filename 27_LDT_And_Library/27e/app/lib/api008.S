    .arch i486

    .global api_initmalloc

// void api_initmalloc(void)
api_initmalloc:
    push %ebx
    movl $8, %edx
    movl %cs:(0x0020), %ebx // Address of malloc area
    movl %ebx, %eax
    addl $32 * 1024, %eax   // Add 32KB
    movl %cs:(0x0000), %ecx // Data segment size
    sub  %eax, %ecx
    int  $0x40
    pop  %ebx
    ret
