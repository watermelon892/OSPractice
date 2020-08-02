#include "bootpack.h"
#include "../lib/my_clib.h"

extern struct KEYBUF keybuf;

void HariMain(void) {
  struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
  char s[40], mcursor[256];
  int mx, my, i;

  init_gdtidt();
  init_pic();

  /* Since the IDT/PIC initialization is completed, */
  /* cancel the CPU interrupt disable.              */
  io_sti();

  init_palette();
  init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);

  mx = (binfo->scrnx - 16) / 2;
  my = (binfo->scrny - 28 - 16) / 2;

  init_mouse_cursor8(mcursor, COL8_008484);
  putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);

  my_sprintf(s, "(%d, %d)", mx, my);
  putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);

  io_out8(PIC0_IMR, 0xf9); // 11111001 : Allow PIC1 and keyboard
  io_out8(PIC1_IMR, 0xef); // 11101111 :  Allow mouse

  for (;;) {
    io_cli();
    if (keybuf.flag == 0) {
      io_stihlt();
    } else {
      i = keybuf.data;
      keybuf.flag = 0;
      io_sti();
      my_sprintf(s, "%04X", i);
      boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 16, 30, 31);
      putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);
    }
  }
}
