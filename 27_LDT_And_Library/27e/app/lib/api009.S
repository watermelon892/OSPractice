    .arch i486

    .global api_malloc

// char* api_malloc(int size)
api_malloc:
    push %ebx
    movl $9, %edx
    movl %cs:(0x0020), %ebx // Address of malloc area
    movl 8(%esp), %ecx      // size
    int  $0x40
    pop  %ebx
    ret
