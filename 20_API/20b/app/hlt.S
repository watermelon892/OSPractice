    .arch i486

    movb 0x41, %al
    call 0x4493

fin:
    hlt
    jmp fin
