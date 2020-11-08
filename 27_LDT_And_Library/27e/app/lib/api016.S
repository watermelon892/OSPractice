    .arch i486

    .global api_alloctimer

// int api_alloctimer(void)
api_alloctimer:
    movl $16, %edx
    int  $0x40
    ret
