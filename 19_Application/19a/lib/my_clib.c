#include "my_clib.h"

int num2asc(char *str, int num, int radix,
            int is_uppercase, int is_zero, int width) {
  int len = 0, digit = 0, is_minus = 0;
  char buf[256] = "";

  if (num < 0) {
    num = ~num;
    num++;
    is_minus = 1;
  }

  for (;;) {
    digit = num % radix;

    if (radix == 2 || radix == 8 || radix == 10) {
      buf[len++] = digit + '0';
    } else if (radix == 16) {
      if (digit < 10) {
        buf[len++] = digit + '0';
      } else {
        if (is_uppercase) {
          buf[len++] = digit - 10 + 'A';
        } else {
          buf[len++] = digit - 10 + 'a';
        }
      }
    } else {
      return -1;
    }

    if (num < radix) {
      if (len < width) {
        for (; len < width ;) {
          if (is_zero) {
            buf[len++] = '0';
          } else {
            buf[len++] = ' ';
          }
        }
      }
      if (is_minus) buf[len++] = '-';
      break;
    }

    num /= radix;
  }

  for (int i = len - 1; 0 <= i; i--) {
    *(str++) = buf[i];
  }

  return len;
}

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
        size = num2asc(str, va_arg(args, int), 10, FALSE, is_zero, width);
        break;
      case 'x':
        size = num2asc(str, va_arg(args, int), 16, FALSE, is_zero, width);
        break;
      case 'X':
        size = num2asc(str, va_arg(args, int), 16, TRUE, is_zero, width);
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

int my_strcmp(char *str1, char *str2) {
  for (; *str1 == *str2; str1++, str2++) {
    if (*str1 == '\0') return 0;
  }
  return *str1 - *str2;
}
