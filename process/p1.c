#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int arvc, char **argv) {
  int x = 100;
  printf("x: %d\n", x);

  pid_t rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    x++;
    printf("(child) x: %d\n", x);
  } else {
    x++;
    printf("(parent) x: %d\n", x);
  }
}
