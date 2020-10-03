    .arch i486

    .extern HariMain
    .global __start

__start:
    call HariMain
    lret

    .global api_putchar
    .global api_putstr0
    .global api_end
    .global api_openwin

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

// int api_openwin(char *buf, int xsiz, int ysiz, int col_inv, char *title)
api_openwin:
    push %edi
    push %esi
    push %ebx
    movl $5, %edx
    movl 16(%esp), %ebx // buf
    movl 20(%esp), %esi // xsiz
    movl 24(%esp), %edi // ysiz
    movl 28(%esp), %eax // col_inv
    movl 32(%esp), %ecx // title
    int  $0x40
    pop  %ebx
    pop  %esi
    pop  %edi
    ret
