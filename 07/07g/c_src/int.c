/* Interrupt */

#include "bootpack.h"
#include "../lib/my_clib.h"

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

#define PORT_KEYDAT 0x0060

struct FIFO8 keyfifo;

/* Interrupt from PS/2 keyboard */
void inthandler21(int *esp) {
  unsigned char data;

  io_out8(PIC0_OCW2, 0x61); // Notify PIC that IRQ-01 has been accepted
  data = io_in8(PORT_KEYDAT);
  fifo8_put(&keyfifo, data);

  return;
}

struct FIFO8 mousefifo;

/* Interrupt from PS/2 mouse  */
void inthandler2c(int *esp) {
  unsigned char data;

  io_out8(PIC1_OCW2, 0x64); // Notify PIC1 that IRQ-12 has been accepted
  io_out8(PIC0_OCW2, 0x62); // Notify PIC0 that IRQ-02 has been accepted
  data = io_in8(PORT_KEYDAT);
  fifo8_put(&mousefifo, data);

  return;
}

/* Incomplete interrupt countermeasure from PIC0 */
void inthandler27(int *esp) {
  io_out8(PIC0_OCW2, 0x67); // Notify PIC of IRQ-07 acceptance
  return;
}
