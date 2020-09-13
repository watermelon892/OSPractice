    .arch i486

    movb  $'H', %al
    int   $0x40

    movb  $'e', %al
    int   $0x40

    movb  $'l', %al
    int   $0x40

    movb  $'l', %al
    int   $0x40

    movb  $'o', %al
    int   $0x40

    lret
