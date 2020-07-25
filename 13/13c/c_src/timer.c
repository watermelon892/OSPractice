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
    timerctl.timers0[i].flags = 0;
  }

  return;
}

struct TIMER *timer_alloc(void) {
  for (int i = 0; i < MAX_TIMER; i++) {
    if (timerctl.timers0[i].flags == 0) {
      timerctl.timers0[i].flags = TIMER_FLAGS_ALLOC;
      return &timerctl.timers0[i];
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
  int e, i, j;

  timer->timeout = timeout + timerctl.count;
  timer->flags   = TIMER_FLAGS_USING;

  e = io_load_eflags();
  io_cli();

  /* Find where to assignment */
  for (i = 0; i < timerctl.using; i++) {
    if (timerctl.timers[i]->timeout >= timer->timeout) break;
  }

  /* Shift the back */
  for (j = timerctl.using; j > i; j--) {
    timerctl.timers[j] = timerctl.timers[j - 1];
  }

  timerctl.using++;

  /* Allocate to open space */
  timerctl.timers[i] = timer;
  timerctl.next = timerctl.timers[0]->timeout;

  io_store_eflags(e);

  return;
}

void inthandler20(int *esp) {
  int i, j;

  io_out8(PIC0_OCW2, 0x60); // Notify PIC that IRQ-00 has been accepted

  timerctl.count++;

  if (timerctl.next > timerctl.count) return;

  timerctl.next = 0xffffffff;

  for (i = 0; i < timerctl.using; i++) {
    /* Not check "flags" because all timers in "timers" are running */
    if (timerctl.timers[i]->timeout > timerctl.count) break;

    /* Timeout */
    timerctl.timers[i]->flags = TIMER_FLAGS_ALLOC;
    fifo8_put(timerctl.timers[i]->fifo, timerctl.timers[i]->data);
  }

  /* Just "i" timers were timeout, so stagger the rest */
  timerctl.using -= i;

  for (j = 0; j < timerctl.using; j++) {
    timerctl.timers[j] = timerctl.timers[i + j];
  }

  if (timerctl.using > 0) {
    timerctl.next = timerctl.timers[0]->timeout;
  } else {
    timerctl.next = 0xffffffff;
  }

  return;
}
