#include "my_clib.h"

void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int  io_load_eflags(void);
void io_store_eflags(int eflags);

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void boxfill8(
  unsigned char *vram,
  int xsize,
  unsigned char c,
  int x0, int y0,
  int x1, int y1
);
void init_screen(char *vram, int x, int y);
void putfont8(char *vram, int xsize, int x, int y, char c, char *font);
void putfonts8_asc(
  char *vram, int xsize,
  int x, int y,
  char c, unsigned char *s
);

#define COL8_000000  0
#define COL8_FF0000  1
#define COL8_00FF00  2
#define COL8_FFFF00  3
#define COL8_0000FF  4
#define COL8_FF00FF  5
#define COL8_00FFFF  6
#define COL8_FFFFFF  7
#define COL8_C6C6C6  8
#define COL8_840000  9
#define COL8_008400 10
#define COL8_848400 11
#define COL8_000084 12
#define COL8_840084 13
#define COL8_008484 14
#define COL8_848484 15

struct BOOTINFO {
  char  cyls, leds, vmode, reserve;
  short scrnx, scrny;
  char  *vram;
};

void HariMain(void) {
  struct BOOTINFO *binfo = (struct BOOTINFO*)0x0ff0;
  char s[40];
  int my_sprintf_return_value = 0;

  init_palette();

  init_screen(binfo->vram, binfo->scrnx, binfo->scrny);

  putfonts8_asc(binfo->vram, binfo->scrnx,  8,  8, COL8_FFFFFF, "ABC 123");
  putfonts8_asc(binfo->vram, binfo->scrnx, 31, 31, COL8_000000, "Haribote OS.");
  putfonts8_asc(binfo->vram, binfo->scrnx, 30, 30, COL8_FFFFFF, "Haribote OS.");

  my_sprintf_return_value = my_sprintf(s, "scrnx = %d", binfo->scrnx);
  putfonts8_asc(binfo->vram, binfo->scrnx, 16, 64, COL8_FFFFFF, s);

  my_sprintf(s, "Return value of my_sprintf: %d", my_sprintf_return_value);
  putfonts8_asc(binfo->vram, binfo->scrnx, 16, 80, COL8_FFFFFF, s);

  for (;;) {
    io_hlt();
  }
}

void init_palette(void) {
  static unsigned char table_rgb[16 * 3] = {
     0x00, 0x00, 0x00,  /*  0: Black             */
     0xff, 0x00, 0x00,  /*  1: Bright Red        */
     0x00, 0xff, 0x00,  /*  2: Bright Green      */
     0xff, 0xff, 0x00,  /*  3: Bright Yellow     */
     0x00, 0x00, 0xff,  /*  4: Bright Blue       */
     0xff, 0x00, 0xff,  /*  5: Bright Purple     */
     0x00, 0xff, 0xff,  /*  6: Bright Light Blue */
     0xff, 0xff, 0xff,  /*  7: White             */
     0xc6, 0xc6, 0xc6,  /*  8: Bright Gray       */
     0x84, 0x00, 0x00,  /*  9: Dark Red          */
     0x00, 0x84, 0x00,  /* 10: Dark Green        */
     0x84, 0x84, 0x00,  /* 11: Dark Yellow       */
     0x00, 0x00, 0x84,  /* 12: Dark Blue         */
     0x84, 0x00, 0x84,  /* 13: Dark Purple       */
     0x00, 0x84, 0x84,  /* 14: Dark Light Blue   */
     0x84, 0x84, 0x84   /* 15: Dark Gray         */
  };

  set_palette(0, 15, table_rgb);

  return;
}

void set_palette(int start, int end, unsigned char *rgb) {
  int i, eflags;

  eflags = io_load_eflags();  // Save the interrupt enable flag value
  io_cli();                   // Disable interrupt
  io_out8(0x03c8, start);

  for (i = start; i <= end; i++) {
    io_out8(0x03c9, rgb[0] / 4);
    io_out8(0x03c9, rgb[1] / 4);
    io_out8(0x03c9, rgb[2] / 4);
    rgb += 3;
  }

  io_store_eflags(eflags);    // Restore interrupt enable flag

  return;
}

void boxfill8(
  unsigned char *vram,
  int xsize,
  unsigned char c,
  int x0, int y0,
  int x1, int y1
) {
  int x, y;

  for (y = y0; y <= y1; y++) {
    for (x = x0; x <= x1; x++) {
      vram[y * xsize + x] = c;
    }
  }

  return;
}

void init_screen(char *vram, int x, int y) {
  boxfill8(vram, x, COL8_008484, 0,      0, x - 1, y - 29);
  boxfill8(vram, x, COL8_C6C6C6, 0, y - 28, x - 1, y - 28);
  boxfill8(vram, x, COL8_FFFFFF, 0, y - 27, x - 1, y - 27);
  boxfill8(vram, x, COL8_C6C6C6, 0, y - 26, x - 1, y -  1);

  boxfill8(vram, x, COL8_FFFFFF,  3, y - 24, 59, y - 24);
  boxfill8(vram, x, COL8_FFFFFF,  2, y - 24,  2, y -  4);
  boxfill8(vram, x, COL8_848484,  3, y -  4, 59, y -  4);
  boxfill8(vram, x, COL8_848484, 59, y - 23, 59, y -  5);
  boxfill8(vram, x, COL8_000000,  2, y -  3, 59, y -  3);
  boxfill8(vram, x, COL8_000000, 60, y - 24, 60, y -  3);

  boxfill8(vram, x, COL8_848484, x - 47, y - 24, x -  4, y - 24);
  boxfill8(vram, x, COL8_848484, x - 47, y - 23, x - 47, y -  4);
  boxfill8(vram, x, COL8_FFFFFF, x - 47, y -  3, x -  4, y -  3);
  boxfill8(vram, x, COL8_FFFFFF, x -  3, y - 24, x -  3, y -  3);

  return;
}

void putfont8(char *vram, int xsize, int x, int y, char c, char *font) {
  int i;
  char *p, d;

  for (i = 0; i < 16; i++) {
    p = vram + (y + i) * xsize + x;
    d = font[i];
    if ((d & 0x80) != 0) { p[0] = c; }
    if ((d & 0x40) != 0) { p[1] = c; }
    if ((d & 0x20) != 0) { p[2] = c; }
    if ((d & 0x10) != 0) { p[3] = c; }
    if ((d & 0x08) != 0) { p[4] = c; }
    if ((d & 0x04) != 0) { p[5] = c; }
    if ((d & 0x02) != 0) { p[6] = c; }
    if ((d & 0x01) != 0) { p[7] = c; }
  }

  return;
}

void putfonts8_asc(
  char *vram, int xsize,
  int x, int y,
  char c, unsigned char *s
) {
  extern char hankaku[4096];
  for (; *s != 0x00; s++) {
    putfont8(vram, xsize, x, y, c, hankaku + *s * 16);
    x += 8;
  }
  return;
}
