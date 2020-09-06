#include "my_clib.h"
#include <stdio.h>

int tests_count = 0;
int ok_count    = 0;
int ng_count    = 0;

void check(int ret);
void my_strcmp_test();
void my_sprintf_test();

int main() {
  printf("\n# My CLIB Test Start!!\n\n");

  my_strcmp_test();
  my_sprintf_test();

  printf("# My CLIB Test End!!\n\n");

  printf("#################### Results ####################\n");
  printf("# All Tests : %d\n", tests_count);
  printf("# OK        : %d\n", ok_count);
  printf("# NG        : %d\n", ng_count);
  printf("#################################################\n");

  return 0;
}

void check(int ret) {
  tests_count += 1;
  printf("Result: ");
  if (ret) {
    ok_count += 1;
    printf("\x1b[32m"); // Color: Green
    printf("OK\n");
  } else {
    ng_count += 1;
    printf("\x1b[31m"); // Color: Red
    printf("NG\n");
  }
  printf("\x1b[0m");    // Color: Default
}

void my_strcmp_test() {
  int ret = 0;

  printf("## my_strcmp Test Start!!\n\n");

  printf("### arg1(12345) == arg2(12345)\n");
  ret = my_strcmp("12345", "12345");
  printf("Value: %d\n", ret);
  check(ret == 0);

  printf("### arg1(12346) > arg2(12345)\n");
  ret = my_strcmp("12346", "12345");
  printf("Value: %d\n", ret);
  check(ret == 1);

  printf("### arg1(12345) < arg2(12346)\n");
  ret = my_strcmp("12345", "12346");
  printf("Value: %d\n", ret);
  check(ret == -1);

  printf("### arg1(123450) > arg2(12345)\n");
  ret = my_strcmp("123450", "12345");
  printf("Value: %d\n", ret);
  check(ret == 48);

  printf("### arg1(12345) < arg2(123450)\n");
  ret = my_strcmp("12345", "123450");
  printf("Value: %d\n", ret);
  check(ret == -48);

  printf("\n## my_strcmp Test End!!\n\n");
}

void my_sprintf_test() {
  char str[256] = "";
  int len = 0;

  printf("## my_sprintf Test Start!!\n\n");

  printf("### format: d, args: 10 \n");
  len = my_sprintf(str, "%d", 10);
  printf("Value: %s\n", str);
  check(len == 2);
  printf("Value: %d\n", len);
  check(my_strcmp(str, "10") == 0);

  printf("### format: x, args: 10 \n");
  len = my_sprintf(str, "%x", 10);
  printf("Value: %s\n", str);
  check(len == 1);
  printf("Value: %d\n", len);
  check(my_strcmp(str, "a") == 0);

  printf("### format: X, args: 10 \n");
  len = my_sprintf(str, "%X", 10);
  printf("Value: %s\n", str);
  check(len == 1);
  printf("Value: %d\n", len);
  check(my_strcmp(str, "A") == 0);

  printf("### format: 2X, args: 10 \n");
  len = my_sprintf(str, "%2X", 10);
  printf("Value: %s\n", str);
  check(len == 2);
  printf("Value: %d\n", len);
  check(my_strcmp(str, " A") == 0);

  printf("### format: 02X, args: 10 \n");
  len = my_sprintf(str, "%02X", 10);
  printf("Value: %s\n", str);
  check(len == 2);
  printf("Value: %d\n", len);
  check(my_strcmp(str, "0A") == 0);

  printf("\n## my_sprintf Test End!!\n\n");
}
