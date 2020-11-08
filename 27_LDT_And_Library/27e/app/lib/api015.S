    .arch i486

    .global api_getkey

// int api_getkey(int mode)
api_getkey:
    movl $15, %edx
    movl 4(%esp), %eax // mode
    int  $0x40
    ret
