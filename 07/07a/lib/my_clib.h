#ifndef __MY_CLIB_H__
#define __MY_CLIB_H__

#include <stdarg.h>

#define TRUE  1
#define FALSE 0

int my_sprintf(char *str, char *format, ...);
int dec2asc(char *str, int dec);
int hex2asc(char *str, int dec, int is_uppercase);

#endif // __MY_CLIB_H__
