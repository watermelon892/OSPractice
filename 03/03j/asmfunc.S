    .arch i486

    .text

    .global _io_hlt  // Function name included in this program

_io_hlt:             // void io_hlt(void);
    hlt
    ret
