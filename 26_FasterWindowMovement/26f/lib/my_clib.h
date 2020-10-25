#ifndef __MY_CLIB_H__
#define __MY_CLIB_H__

#include <stdarg.h>

#define TRUE  1
#define FALSE 0

int my_sprintf(char *str, char *format, ...);
int my_strcmp(char *str1, char *str2);
int my_strncmp(char *str1, char *str2, int size);
int my_rand(void);

#endif // __MY_CLIB_H__
