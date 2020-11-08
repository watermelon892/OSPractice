    .arch i486

    .global api_putstr0

// void api_putstr0(char *s)
api_putstr0:
    push %ebx
    movl $2, %edx
    movl 8(%esp), %ebx // s
    int  $0x40
    pop  %ebx
    ret
