/* Interrupt */

#include "bootpack.h"

void init_pic(void) {
  io_out8(PIC0_IMR, 0xff);    // Do not accept all interrupts
  io_out8(PIC1_IMR, 0xff);    // Do not accept all interrupts

  io_out8(PIC0_ICW1, 0x11);   // Edge trigger mode
  io_out8(PIC0_ICW2, 0x20);   // IRQ0-7 is INT20-27
  io_out8(PIC0_ICW3, 1 << 2); // PIC1 is connected by IRQ2
  io_out8(PIC0_ICW4, 0x01);   // Non-buffer mode

  io_out8(PIC1_ICW1, 0x11);   // Edge trigger mode
  io_out8(PIC1_ICW2, 0x28);   // IRQ8-15 is INT28-2f
  io_out8(PIC1_ICW3, 2);      // PIC1 is connected by IRQ2
  io_out8(PIC1_ICW4, 0x01);   // Non-buffer mode

  io_out8(PIC0_IMR, 0xfb);    // 11111011 : All except PIC1 prohibited
  io_out8(PIC1_IMR, 0xff);    // 11111111 : Not accept all interrupts
}

/* Interrupt from PS/2 keyboard */
void inthandler21(int *esp) {
  struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
  boxfill8(binfo->vram, binfo->scrnx, COL8_000000, 0, 0, 32 * 8 - 1, 15);
  putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF,
                "INT 21 (IRQ-1) : PS/2 keyboard");
  for (;;) {
    io_hlt();
  }
}

/* Interrupt from PS/2 mouse  */
void inthandler2c(int *esp) {
  struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
  boxfill8(binfo->vram, binfo->scrnx, COL8_000000, 0, 0, 32 * 8 - 1, 15);
  putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF,
                "INT 21 (IRQ-1) : PS/2 mouse");
  for (;;) {
    io_hlt();
  }
}

/* Incomplete interrupt countermeasure from PIC0 */
void inthandler27(int *esp) {
  io_out8(PIC0_OCW2, 0x67); // Notify PIC of IRQ-07 acceptance
  return;
}
