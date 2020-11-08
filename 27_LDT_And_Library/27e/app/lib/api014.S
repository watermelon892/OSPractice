    .arch i486

    .global api_closewin

// void api_closewin(int win)
api_closewin:
    push %ebx
    movl $14, %edx
    movl 8(%esp), %ebx // win
    int  $0x40
    pop  %ebx
    ret
