    .arch i486

    movb  $'H', %al
    lcall $2*8, $0x4498

    movb  $'e', %al
    lcall $2*8, $0x4498

    movb  $'l', %al
    lcall $2*8, $0x4498

    movb  $'l', %al
    lcall $2*8, $0x4498

    movb  $'o', %al
    lcall $2*8, $0x4498

    lret
