    .arch i486

    .extern HariMain
    .global __start

__start:
    call HariMain
    lret

    .global api_putchar
    .global api_end

// void api_putchar(int c)
api_putchar:
    mov $1, %edx
    mov 4(%esp), %al  // c
    int $0x40
    ret

api_end:
    mov $4, %edx
    int $0x40
