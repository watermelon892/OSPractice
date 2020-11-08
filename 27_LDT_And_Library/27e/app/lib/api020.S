    .arch i486

    .global api_beep

// void api_beep(int tone)
api_beep:
    movl $20, %edx
    movl 4(%esp), %eax // tone
    int  $0x40
    ret
