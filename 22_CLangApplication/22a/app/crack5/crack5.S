    .arch i486

// "helloos.map"
// .text 0x0000000000004526 0x198 target/asmfunc.o
//       0x0000000000004526 io_hlt
//       0x0000000000004528 io_cli
    call $2 * 8, $0x4528

    movl $4, %edx
    int  $0x40
