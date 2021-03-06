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
  timerctl.next  = 0xffffffff; // Because at first there is no timer running

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
  timer->timeout = timeout + timerctl.count;
  timer->flags   = TIMER_FLAGS_USING;

  if (timerctl.next > timer->timeout) {
    timerctl.next = timer->timeout; // Update next time
  }

  return;
}

void inthandler20(int *esp) {
  io_out8(PIC0_OCW2, 0x60); // Notify PIC that IRQ-00 has been accepted

  timerctl.count++;

  if (timerctl.next > timerctl.count) return;

  timerctl.next = 0xffffffff;

  for (int i = 0; i < MAX_TIMER; i++) {
    if (timerctl.timer[i].flags == TIMER_FLAGS_USING) {
      if (timerctl.timer[i].timeout <= timerctl.count) {
        /* Timeout */
        timerctl.timer[i].flags = TIMER_FLAGS_ALLOC;
        fifo8_put(timerctl.timer[i].fifo, timerctl.timer[i].data);
      } else {
        /* Not timeout yet */
        if (timerctl.next > timerctl.timer[i].timeout) {
          timerctl.next = timerctl.timer[i].timeout;
        }
      }
    }
  }

  return;
}
