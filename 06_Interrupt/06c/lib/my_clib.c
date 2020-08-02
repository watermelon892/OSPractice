#include "my_clib.h"

int my_sprintf(char *str, char *format, ...) {
  va_list args;
  int size, len;

  size = 0;
  len  = 0;

  va_start(args, format);

  for (; *format ;) {
    if (*format == '%') {
      format++;
      switch (*format) {
      case 'd':
        size = dec2asc(str, va_arg(args, int));
        break;
      case 'x':
        size = hex2asc(str, va_arg(args, int));
        break;
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

int dec2asc(char *str, int dec) {
  int len = 0, len_buff;
  int buff[10];

  for (;;) {
    buff[len++] = dec % 10;
    if (dec < 10) break;
    dec /= 10;
  }

  len_buff = len;

  for (; len ;) {
    --len;
    *(str++) = buff[len] + 0x30;
  }

  return len_buff;
}

int hex2asc(char *str, int dec) {
  int len = 0, len_buff;
  int buff[10];

  for (;;) {
    buff[len++] = dec % 16;
    if (dec < 16) break;
    dec /= 16;
  }

  len_buff = len;

  for (; len ;) {
    len--;
    if (buff[len] < 10) {
      *(str++) = buff[len] + 0x30;
    } else {
      *(str++) = buff[len] - 9 + 0x60;
    }
  }

  return len_buff;
}
