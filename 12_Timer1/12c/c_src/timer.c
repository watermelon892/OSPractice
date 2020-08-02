/* Timer */

#include "bootpack.h"

#define PIT_CTRL 0x0043
#define PIT_CNT0 0x0040

struct TIMERCTL timerctl;

void init_pit(void) {
  io_out8(PIT_CTRL, 0x34);
  /* interrupt cycle : 11,932(0x2e9c), frequency : 100Hz */
  io_out8(PIT_CNT0, 0x9c);  // Lower 8 bits of interrupt cycle
  io_out8(PIT_CNT0, 0x2e);  // Upper 8 bits of interrupt cycle
  timerctl.count = 0;
  timerctl.timeout = 0;
}

void inthandler20(int *esp) {
  io_out8(PIC0_OCW2, 0x60); // Notify PIC that IRQ-00 has been accepted

  timerctl.count++;

  if (timerctl.timeout > 0) {  // Is timeout set?
    timerctl.timeout--;
    if (timerctl.timeout == 0) {
      /* Send data to the FIFO buffer */
      fifo8_put(timerctl.fifo, timerctl.data);
    }
  }

  return;
}

void settimer(unsigned int timeout, struct FIFO8 *fifo, unsigned char data) {
  int eflags = io_load_eflags();
  io_cli();
  timerctl.timeout = timeout;
  timerctl.fifo = fifo;
  timerctl.data = data;
  io_store_eflags(eflags);
  return;
}
