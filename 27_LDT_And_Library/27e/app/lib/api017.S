    .arch i486

    .global api_inittimer

// void api_inittimer(int timer, int data)
api_inittimer:
    push %ebx
    movl $17, %edx
    movl  8(%esp), %ebx // timer
    movl 12(%esp), %eax // data
    int  $0x40
    pop  %ebx
    ret
