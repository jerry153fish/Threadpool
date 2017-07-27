#include <stdio.h>
#include <stdlib.h>
#include "job.h"

void print_test(void *s) {
  char *a = (char *)s;
  printf("%s\n", a);
}

int main(int argc, char **argv) {
  fn f = print_test;
  char *s = "hello";
  job j = job_init(f, (void *)s);
  run_job(j);
}
