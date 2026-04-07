#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (fork()) exit(0);
  if (isatty(STDOUT_FILENO)) freopen("/dev/null", "w", stdout);
  if (isatty(STDERR_FILENO)) freopen("/dev/null", "w", stderr);
  setvbuf(stdout, NULL, _IOLBF, 0);
  setvbuf(stderr, NULL, _IOLBF, 0);
  execvp(argv[1], &argv[1]);
  return 0;
}
