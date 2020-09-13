    .arch i486

    movb  $0x41, %al
    lcall $2*8, $0x4493

fin:
    hlt
    jmp fin
