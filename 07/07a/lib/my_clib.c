#include "my_clib.h"

int my_sprintf(char *str, char *format, ...) {
  va_list args;
  int size = 0;
  int len = 0;
  int is_zero, width;

  va_start(args, format);

  for (; *format ;) {
    if (*format == '%') {
      format++;

      is_zero = FALSE;
      width = 0;

      if (*format == '0') {
        format++;
        is_zero = TRUE;
      }

      if ((*format >= '0') && (*format <= '9')) {
        width = *(format++) - '0';
      }

      switch (*format) {
      case 'd':
        size = dec2asc(str, va_arg(args, int), is_zero, width);
        break;
      case 'x':
        size = hex2asc(str, va_arg(args, int), FALSE, is_zero, width);
        break;
      case 'X':
        size = hex2asc(str, va_arg(args, int), TRUE, is_zero, width);
      default:
        len++;
        break;
      }

      len += size;
      str += size;
      format++;

    } else {
      *(str++) = *(format++);
      len++;
    }
  }

  *str = '\0';

  va_end(args);

  return len;
}

int dec2asc(char *str, int dec, int is_zero, int width) {
  int len = 0, len_buff;
  int buff[10];

  for (;;) {
    buff[len++] = dec % 10;
    if (dec < 10) break;
    dec /= 10;
  }

  if (is_zero) {
    for (; len < width ;) {
      buff[len++] = 0x00;
    }
  }

  len_buff = len;

  for (; len ;) {
    --len;
    *(str++) = buff[len] + 0x30;
  }

  return len_buff;
}

int hex2asc(char *str, int dec, int is_uppercase, int is_zero, int width) {
  int len = 0, len_buff, base;
  int buff[10];

  if (is_uppercase) {
    base = 0x40;
  } else {
    base = 0x60;
  }

  for (;;) {
    buff[len++] = dec % 16;
    if (dec < 16) break;
    dec /= 16;
  }

  if (is_zero) {
    for (; len < width ;) {
      buff[len++] = 0x00;
    }
  }

  len_buff = len;

  for (; len ;) {
    len--;
    if (buff[len] < 10) {
      *(str++) = buff[len] + 0x30;
    } else {
      *(str++) = buff[len] - 9 + base;
    }
  }

  return len_buff;
}
