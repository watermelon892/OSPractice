    .arch i486

    .global api_point

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
