int api_openwin(char *buf, int xsiz, int ysiz, int col_inv, char *title);
void api_boxfilwin(int win, int x0, int y0, int x1, int y1, int col);
void api_initmalloc(void);
char* api_malloc(int size);
void api_point(int win, int x, int y, int col);
void api_refreshwin(int win, int x0, int y0, int x1, int y1);
void api_end(void);

int my_rand(void);

void HariMain(void) {
  char *buf;
  int win, i, x, y;

  api_initmalloc();
  buf = api_malloc(150 * 100);
  win = api_openwin(buf, 150, 100, -1, "stars");
  api_boxfilwin(win, 6, 26, 143, 93, 0 /* black */ );
  for (i = 0; i < 50; i++) {
    x = (my_rand() % 137) +  6;
    y = (my_rand() %  67) + 26;
    api_point(win, x, y, 3 /* yellow */);
  }
  api_refreshwin(win, 6, 26, 144, 94);
  api_end();
}

int my_rand() {
  /* Linear congruential generators */
  static int seed = 10;
  int unit_max = 2147483647;
  int a = 1103515245, b = 12345;

  /* Xi+1 = a * Xi + b mod m */
  seed = (a * seed + b) & unit_max;

  return seed;
}
