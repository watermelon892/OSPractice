    .arch i486

    .global api_freetimer

// void api_freetimer(int timer)
api_freetimer:
    push %ebx
    movl $19, %edx
    movl 8(%esp), %ebx // timer
    int  $0x40
    pop  %ebx
    ret
