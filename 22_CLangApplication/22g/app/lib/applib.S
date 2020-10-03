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
    .global api_putstrwin
    .global api_boxfilwin

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

// void api_putstrwin(int win, int x, int y, int col, int len, char *str)
api_putstrwin:
    push %edi
    push %esi
    push %ebp
    push %ebx
    movl $6, %edx
    movl 20(%esp), %ebx // win
    movl 24(%esp), %esi // x
    movl 28(%esp), %edi // y
    movl 32(%esp), %eax // col
    movl 36(%esp), %ecx // len
    movl 40(%esp), %ebp // str
    int  $0x40
    pop  %ebx
    pop  %ebp
    pop  %esi
    pop  %edi
    ret

// void api_boxfilwin(int win, int x0, int y0, int x1, int y1, int col)
api_boxfilwin:
    push %edi
    push %esi
    push %ebp
    push %ebx
    movl $7, %edx
    movl 20(%esp), %ebx // win
    movl 24(%esp), %eax // x0
    movl 28(%esp), %ecx // y0
    movl 32(%esp), %esi // x1
    movl 36(%esp), %edi // y2
    movl 40(%esp), %ebp // col
    int  $0x40
    pop  %ebx
    pop  %ebp
    pop  %esi
    pop  %edi
    ret
