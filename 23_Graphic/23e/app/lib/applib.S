    .arch i486

    .extern HariMain
    .global __start
    .global api_putchar
    .global api_putstr0
    .global api_end
    .global api_openwin
    .global api_putstrwin
    .global api_boxfilwin
    .global api_initmalloc
    .global api_malloc
    .global api_free
    .global api_point
    .global api_refreshwin
    .global api_linewin
    .global api_closewin

__start:
    call HariMain
    lret

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

// char* api_malloc(int size)
api_malloc:
    push %ebx
    movl $9, %edx
    movl %cs:(0x0020), %ebx // Address of malloc area
    movl 8(%esp), %ecx      // size
    int  $0x40
    pop  %ebx
    ret

// void api_free(char *addr, int size)
api_free:
    push %ebx
    movl $10, %edx
    movl %cs:(0x0020), %ebx // Address of malloc area
    movl 8(%esp), %eax      // addr
    movl 12(%esp), %ecx     // size
    int  $0x40
    pop  %ebx
    ret

// void api_point(int win, int x, int y, int col)
api_point:
    push %edi
    push %esi
    push %ebx
    movl $11, %edx
    movl 16(%esp), %ebx // win
    movl 20(%esp), %esi // x
    movl 24(%esp), %edi // y
    movl 28(%esp), %eax // col
    int  $0x40
    pop  %ebx
    pop  %esi
    pop  %edi
    ret

// void api_refreshwin(int win, int x0, int y0, int x1, int y1)
api_refreshwin:
    push %edi
    push %esi
    push %ebx
    movl $12, %edx
    movl 16(%esp), %ebx // win
    movl 20(%esp), %eax // x0
    movl 24(%esp), %ecx // y0
    movl 28(%esp), %esi // x1
    movl 32(%esp), %edi // y1
    int  $0x40
    pop  %ebx
    pop  %esi
    pop  %edi
    ret

// void api_linewin(int win, int x0, int y0, int x1, int y1, int col)
api_linewin:
    push %edi
    push %esi
    push %ebp
    push %ebx
    movl $13, %edx
    movl 20(%esp), %ebx // win
    movl 24(%esp), %eax // x0
    movl 28(%esp), %ecx // y0
    movl 32(%esp), %esi // x1
    movl 36(%esp), %edi // y1
    movl 40(%esp), %ebp // col
    int  $0x40
    pop  %ebx
    pop  %ebp
    pop  %esi
    pop  %edi
    ret

// void api_closewin(int win)
api_closewin:
    push %ebx
    movl $14, %edx
    movl 8(%esp), %ebx // win
    int  $0x40
    pop  %ebx
    ret
