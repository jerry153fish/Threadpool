#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "j_threadpool.h"
#include "j_queue.h"
#include "job.h"
// simple declare universal struct
static int pool_alive = 1;


void print_test(void *s) {
  char *a = (char *)s;
  printf("%s\n", a);
}

int main(int argc, char **argv) {
  threadpool tp = threadpool_init(4);
  fn f = print_test;
  char *s1 = "haa";
  char *s2 = "haa1";
  pool_add_fn(tp, f, (void *)s1);
  pool_add_fn(tp, f, (void *)s2);
  pool_add_fn(tp, f, (void *)s2);
  pool_add_fn(tp, f, (void *)s2);
  pool_add_fn(tp, f, (void *)s2);
  pool_add_fn(tp, f, (void *)s2);
  pool_add_fn(tp, f, (void *)s2);

  pool_add_fn(tp, f, (void *)s2);
  sleep(5);
  pool_destroy(tp);
  return 0;
}
