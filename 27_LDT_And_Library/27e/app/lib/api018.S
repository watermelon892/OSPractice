    .arch i486

    .global api_settimer

// void api_settimer(int timer, int time)
api_settimer:
    push %ebx
    movl $18, %edx
    movl  8(%esp), %ebx // timer
    movl 12(%esp), %eax // time
    int  $0x40
    pop  %ebx
    ret
