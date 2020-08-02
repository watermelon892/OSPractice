    .arch i486

    .text

    // Function name included in this program
    .global io_hlt

// void _io_hlt(void)
io_hlt:
    hlt
    ret
