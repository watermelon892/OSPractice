/* Console */

#include "bootpack.h"
#include "../lib/my_clib.h"

void console_task(struct SHEET *sheet, unsigned int memtotal) {
  struct TIMER *timer;
  struct TASK *task = task_now();
  int i, fifobuf[128], cursor_x = 16, cursor_y = 28, cursor_c = -1, fx = 0;;
  char s[30], cmdline[30], *p;
  struct MEMMAN *memman = (struct MEMMAN *)MEMMAN_ADDR;
  struct FILEINFO *finfo = (struct FILEINFO *)(ADR_DISKIMG + 0x002600);
  int *fat = (int *)memman_alloc_4k(memman, 4 + 2880);
  struct SEGMENT_DESCRIPTOR *gdt = (struct SEGMENT_DESCRIPTOR *)ADR_GDT;

  fifo32_init(&task->fifo, 128, fifobuf, task);

  timer = timer_alloc();
  timer_init(timer, &task->fifo, 1);
  timer_settime(timer, 50);

  file_readfat(fat, (unsigned char *)(ADR_DISKIMG + 0x000200));

  putfonts8_asc_sht(sheet, 8, 28, COL8_FFFFFF, COL8_000000, ">", 1);

  for (;;) {
    io_cli();
    if (fifo32_status(&task->fifo) == 0) {
      task_sleep(task);
      io_sti();
    } else {
      i = fifo32_get(&task->fifo);
      io_sti();
      if (i <= 1) {
        /* Timer for cursor */
        if (i != 0) {
          timer_init(timer, &task->fifo, 0);
          if (cursor_c >= 0) {
            cursor_c = COL8_FFFFFF;
          }
        } else {
          timer_init(timer, &task->fifo, 1);
          if (cursor_c >= 0) {
            cursor_c = COL8_000000;
          }
        }
        timer_settime(timer, 50);
      }
      if (i == 2) {
        /* Turn on the cursor */
        cursor_c = COL8_FFFFFF;
      }
      if (i == 3) {
        /* Turn off the cursor */
        boxfill8(sheet->buf, sheet->bxsize, COL8_000000,
                 cursor_x, cursor_y, cursor_x + 7, 43);
        cursor_c = -1;
      }
      if (256 <= i && i <= 511) {
        /* Keyboard Data */
        if (i == 8 + 256) {
          /* Backspace */
          if (cursor_x > 16) {
            putfonts8_asc_sht(sheet, cursor_x, cursor_y,
                              COL8_FFFFFF, COL8_000000, " ", 1);
            cursor_x -= 8;
          }
        } else if (i == 10 + 256) {
          /* Enter */
          /* Turn off the cursor at Enter */
          putfonts8_asc_sht(sheet, cursor_x, cursor_y,
                            COL8_FFFFFF, COL8_000000, " ", 1);
          cmdline[cursor_x / 8 - 2] = 0;
          cursor_y = cons_newline(cursor_y, sheet);
          /* Command execution */
          if (my_strcmp(cmdline, "mem") == 0) {
            /* mem command */
            my_sprintf(s, "total   %dMB", memtotal / (1024 * 1024));
            putfonts8_asc_sht(sheet, 8, cursor_y,
                              COL8_FFFFFF, COL8_000000, s, 30);
            cursor_y = cons_newline(cursor_y, sheet);
            my_sprintf(s, "free %dKB", memman_total(memman) / 1024);
            putfonts8_asc_sht(sheet, 8, cursor_y,
                              COL8_FFFFFF, COL8_000000, s, 30);
            cursor_y = cons_newline(cursor_y, sheet);
            cursor_y = cons_newline(cursor_y, sheet);
          } else if (my_strcmp(cmdline, "cls") == 0) {
            /* cls command */
            for (int y = 28; y < 28 + 128; y++) {
              for (int x = 8; x < 8 + 240; x++) {
                sheet->buf[x + y * sheet->bxsize] = COL8_000000;
              }
            }
            sheet_refresh(sheet, 8, 28, 8 + 240, 28 + 128);
            cursor_y = 28;
          } else if (my_strcmp(cmdline, "dir") == 0) {
            /* dir command */
            for (int x = 0; x < 224; x++) {
              if (finfo[x].name[0] == 0x00) break;
              if (finfo[x].name[0] != 0xe5) {
                if ((finfo[x].type & 0x18) == 0) {
                  my_sprintf(s, "filename.ext   %7d", finfo[x].size);
                  for (int y = 0; y < 8; y++) {
                    s[y] = finfo[x].name[y];
                  }
                  s[ 9] = finfo[x].ext[0];
                  s[10] = finfo[x].ext[1];
                  s[11] = finfo[x].ext[2];
                  putfonts8_asc_sht(sheet, 8, cursor_y,
                                    COL8_FFFFFF, COL8_000000, s, 30);
                  cursor_y = cons_newline(cursor_y, sheet);
                }
              }
            }
            cursor_y = cons_newline(cursor_y, sheet);
          } else if (my_strncmp(cmdline, "type ", 5) == 0) {
            /* type command */
            /* Prepare the file name */
            for (int y = 0; y < 11; y++) {
              s[y] = ' ';
            }
            for (int x = 5, y = 0; y < 11 && cmdline[x] != 0; x++) {
              if (cmdline[x] == '.' && y <= 8) {
                y = 8;
              } else {
                s[y] = cmdline[x];
                if ('a' <= s[y] && s[y] <= 'z') {
                  /* Lowercase to uppercase */
                  s[y] -= 0x20;
                }
                y++;
              }
            }
            /* Find file */
            for (fx = 0; fx < 224; ) {
              if (finfo[fx].name[0] == 0x00) break;
              if ((finfo[fx].type & 0x18) == 0) {
                for (int y = 0; y < 11; y++) {
                  if (finfo[fx].name[y] != s[y]) goto type_next_file;
                }
                break;
              }
            type_next_file:
              fx++;
            }
            if (fx < 224 && finfo[fx].name[0] != 0x00) {
              /* If the file is found */
              p = (char *)memman_alloc_4k(memman, finfo[fx].size);
              file_loadfile(finfo[fx].clustno, finfo[fx].size, p, fat,
                            (char *)(ADR_DISKIMG + 0x003e00));
              cursor_x = 8;
              for (int y = 0; y < finfo[fx].size; y++) {
                s[0] = p[y];
                s[1] = 0;
                if (s[0] == 0x09) {
                  /* Tab */
                  for (;;) {
                    putfonts8_asc_sht(sheet, cursor_x, cursor_y,
                                      COL8_FFFFFF, COL8_000000, " ", 1);
                    cursor_x += 8;
                    if (cursor_x == 8 + 240) {
                      cursor_x = 8;
                      cursor_y = cons_newline(cursor_y, sheet);
                    }
                    if (((cursor_x - 8) & 0x1f) == 0) {
                      /* Break if divisible by 32 */
                      break;
                    }
                  }
                } else if (s[0] == 0x0a) {
                  /* Newline */
                  cursor_x = 8;
                  cursor_y = cons_newline(cursor_y, sheet);
                } else if (s[0] == 0x0d) {
                  /* Carriage Return */
                  /* Do nothing */
                } else {
                  /* General characters */
                  putfonts8_asc_sht(sheet, cursor_x, cursor_y,
                                    COL8_FFFFFF, COL8_000000, s, 1);
                  cursor_x += 8;
                  if (cursor_x == 8 + 240) {
                    cursor_x = 8;
                    cursor_y = cons_newline(cursor_y, sheet);
                  }
                }
              }
              memman_free_4k(memman, (int)p, finfo[fx].size);
            } else {
              /* If the file is not found */
              putfonts8_asc_sht(sheet, 8, cursor_y,
                                COL8_FFFFFF, COL8_000000,
                                "File not fount.", 15);
              cursor_y = cons_newline(cursor_y, sheet);
            }
            cursor_y = cons_newline(cursor_y, sheet);
          } else if (my_strcmp(cmdline, "hlt") == 0) {
            /* Launch the HLT application */
            for (int y = 0; y < 11; y++) {
              s[y] = ' ';
            }
            s[0]  = 'H';
            s[1]  = 'L';
            s[2]  = 'T';
            s[8]  = 'H';
            s[9]  = 'R';
            s[10] = 'B';
            for (fx = 0; fx < 224;) {
              if (finfo[fx].name[0] == 0x00) break;
              if ((finfo[fx].type & 0x18) == 0) {
                for (int y = 0; y < 11; y++) {
                  if (finfo[fx].name[y] != s[y]) goto hlt_next_file;
                }
                break;
              }
            hlt_next_file:
              fx++;
            }
            if (fx < 224 && finfo[fx].name[0] != 0x00) {
              p = (char *)memman_alloc_4k(memman, finfo[fx].size);
              file_loadfile(finfo[fx].clustno, finfo[fx].size, p, fat,
                            (char *)(ADR_DISKIMG + 0x003e00));
              set_segmdesc(gdt + 1003, finfo[fx].size - 1,
                           (int)p, AR_CODE32_ER);
              farjmp(0, 1003 * 8);
              memman_free_4k(memman, (int)p, finfo[fx].size);
            } else {
              /* If the file is not found */
              putfonts8_asc_sht(sheet, 8, cursor_y,
                                COL8_FFFFFF, COL8_000000,
                                "File not fount.", 15);
              cursor_y = cons_newline(cursor_y, sheet);
            }
            cursor_y = cons_newline(cursor_y, sheet);
          } else if (cmdline[0] != 0) {
            putfonts8_asc_sht(sheet, 8, cursor_y,
                              COL8_FFFFFF, COL8_000000,
                              "Bad command.", 12);
            cursor_y = cons_newline(cursor_y, sheet);
            cursor_y = cons_newline(cursor_y, sheet);
          }
          /* Show prompt */
          putfonts8_asc_sht(sheet, 8, cursor_y,
                            COL8_FFFFFF, COL8_000000, ">", 1);
          cursor_x = 16;
        } else {
          /* General character */
          if (cursor_x < 240) {
            s[0] = i - 256;
            s[1] = 0;
            cmdline[cursor_x / 8 - 2] = i - 256;
            putfonts8_asc_sht(sheet, cursor_x, cursor_y,
                              COL8_FFFFFF, COL8_000000, s, 1);
            cursor_x += 8;
          }
        }
      }
      if (cursor_c >= 0) {
        boxfill8(sheet->buf, sheet->bxsize, cursor_c,
                 cursor_x, cursor_y,
                 cursor_x + 7, cursor_y + 15);
      }
      sheet_refresh(sheet, cursor_x, cursor_y, cursor_x + 8, cursor_y + 16);
    }
  }
}

int cons_newline(int cursor_y, struct SHEET *sheet) {
  if (cursor_y < 28 + 112) {
    cursor_y += 16; // To next line
  } else {
    /* Scroll */
    for (int y = 28; y < 28 + 112; y++) {
      for (int x = 8; x < 8 + 240; x++) {
        sheet->buf[x + y * sheet->bxsize]
          = sheet->buf[x + (y + 16) * sheet->bxsize];
      }
    }
    for (int y = 28 + 112; y < 28 + 128; y++) {
      for (int x = 8; x < 8 + 240; x++) {
        sheet->buf[x + y * sheet->bxsize] = COL8_000000;
      }
    }
    sheet_refresh(sheet, 8, 28, 8 + 240, 28 + 128);
  }
  return cursor_y;
}
