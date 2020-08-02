/* Timer */

#include "bootpack.h"

#define PIT_CTRL 0x0043
#define PIT_CNT0 0x0040

struct TIMERCTL timerctl;

#define TIMER_FLAGS_ALLOC 1  // Allocated state
#define TIMER_FLAGS_USING 2  // Timer is running

void init_pit(void) {
  io_out8(PIT_CTRL, 0x34);
  /* interrupt cycle : 11,932(0x2e9c), frequency : 100Hz */
  io_out8(PIT_CNT0, 0x9c);  // Lower 8 bits of interrupt cycle
  io_out8(PIT_CNT0, 0x2e);  // Upper 8 bits of interrupt cycle

  timerctl.count = 0;

  for (int i = 0; i < MAX_TIMER; i++) {
    timerctl.timer[i].flags = 0;
  }

  return;
}

struct TIMER *timer_alloc(void) {
  for (int i = 0; i < MAX_TIMER; i++) {
    if (timerctl.timer[i].flags == 0) {
      timerctl.timer[i].flags = TIMER_FLAGS_ALLOC;
      return &timerctl.timer[i];
    }
  }
  return 0;
}

void timer_free(struct TIMER *timer) {
  timer->flags = 0; // Unused
  return;
}

void timer_init(struct TIMER *timer, struct FIFO8 *fifo, unsigned char data) {
  timer->fifo = fifo;
  timer->data = data;
  return;
}

void timer_settime(struct TIMER *timer, unsigned int timeout) {
  timer->timeout = timeout;
  timer->flags   = TIMER_FLAGS_USING;
  return;
}

void inthandler20(int *esp) {
  io_out8(PIC0_OCW2, 0x60); // Notify PIC that IRQ-00 has been accepted

  timerctl.count++;

  for (int i = 0; i < MAX_TIMER; i++) {
    if (timerctl.timer[i].flags == TIMER_FLAGS_USING) {
      timerctl.timer[i].timeout--;
      if (timerctl.timer[i].timeout == 0) {
        timerctl.timer[i].flags = TIMER_FLAGS_ALLOC;
        /* Send data to the FIFO buffer */
        fifo8_put(timerctl.timer[i].fifo, timerctl.timer[i].data);
      }
    }
  }

  return;
}
