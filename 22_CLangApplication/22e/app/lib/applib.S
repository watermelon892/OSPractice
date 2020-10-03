    .arch i486

    .extern HariMain
    .global __start

__start:
    call HariMain
    lret

    .global api_putchar
    .global api_putstr0
    .global api_end

// void api_putchar(int c)
api_putchar:
    mov $1, %edx
    mov 4(%esp), %al  // c
    int $0x40
    ret

// void api_putstr0(char *s)
api_putstr0:
    push %ebx
    movl $2, %edx
    movl 8(%esp), %ebx // s
    int  $0x40
    pop  %ebx
    ret

// void api_end(void)
api_end:
    mov $4, %edx
    int $0x40
