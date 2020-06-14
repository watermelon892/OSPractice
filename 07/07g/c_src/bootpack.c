#include "bootpack.h"
#include "../lib/my_clib.h"

extern struct FIFO8 keyfifo, mousefifo;
void enable_mouse(void);
void init_keyboard(void);

void HariMain(void) {
  struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
  char s[40], mcursor[256], keybuf[32], mousebuf[128];
  int mx, my, i;

  init_gdtidt();
  init_pic();

  /* Since the IDT/PIC initialization is completed, */
  /* cancel the CPU interrupt disable.              */
  io_sti();

  fifo8_init(&keyfifo, 32, keybuf);
  fifo8_init(&mousefifo, 128, mousebuf);
  io_out8(PIC0_IMR, 0xf9); // 11111001 : Allow PIC1 and keyboard
  io_out8(PIC1_IMR, 0xef); // 11101111 :  Allow mouse

  init_keyboard();

  init_palette();
  init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);

  mx = (binfo->scrnx - 16) / 2;
  my = (binfo->scrny - 28 - 16) / 2;

  init_mouse_cursor8(mcursor, COL8_008484);
  putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);

  my_sprintf(s, "(%d, %d)", mx, my);
  putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);

  enable_mouse();

  for (;;) {
    io_cli();
    if (fifo8_status(&keyfifo) + fifo8_status(&mousefifo) == 0) {
      io_stihlt();
    } else {
      if (fifo8_status(&keyfifo) != 0) {
        i = fifo8_get(&keyfifo);
        io_sti();
        my_sprintf(s, "%02X", i);
        boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 16, 15, 31);
        putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);
      } else if (fifo8_status(&mousefifo) != 0) {
        i = fifo8_get(&mousefifo);
        io_sti();
        my_sprintf(s, "%02X", i);
        boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 32, 16, 47, 31);
        putfonts8_asc(binfo->vram, binfo->scrnx, 32, 16, COL8_FFFFFF, s);
      }
    }
  }
}

#define PORT_KEYDAT          0x0060
#define PORT_KEYSTA          0x0064
#define PORT_KEYCMD          0x0064
#define KEYSTA_SEND_NOTREADY 0x02
#define KEYCMD_WRITE_MODE    0x60
#define KBC_MODE             0x47

/* Wait for the keyboard controller to be ready to send data */
void wait_KBC_sendready(void) {
  for (;;) {
    if ((io_in8(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY) == 0) {
      break;
    }
  }
  return;
}

/* Keyboard controller initialization */
void init_keyboard(void) {
  wait_KBC_sendready();
  io_out8(PORT_KEYCMD, KEYCMD_WRITE_MODE);
  wait_KBC_sendready();
  io_out8(PORT_KEYDAT, KBC_MODE);
  return;
}

#define KEYCMD_SENDTO_MOUSE 0xd4
#define MOUSECMD_ENABLE     0xf4

void enable_mouse(void) {
  wait_KBC_sendready();
  io_out8(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);
  wait_KBC_sendready();
  io_out8(PORT_KEYDAT, MOUSECMD_ENABLE);
  return;
}
