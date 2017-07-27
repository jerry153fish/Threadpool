#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#include "job.h"
#include "j_queue.h"

void print_test(void *s) {
  char *a = (char *)s;
  printf("%s\n", a);
}

typedef struct arg_str {
  j_queue q;
  fn f;
  char arg[50];
} *arg;

void *thread_add(void *a) {
  arg a1 = (arg)a;
  q_put(a1->q, a1->f, (void *)a1->arg);
  free(a);
}

void *thread_get(void *q) {
  j_queue q1 = (j_queue)q;
  for (int i = 0; i < 2; i++) {
    job a = q_get(q1);
    run_job(a);
  }
}

int main(int argc, char **argv) {
  pthread_t threads[10];
  pthread_t threads1[3];
  j_queue q = q_init();
  fn f = print_test;
  fn f1 = print_test;

  char *args[10] = { "h1", "h2", "ad3", "cd4", "sdf5", "h6", "h7", "ad83", "cd94", "sdf10"};

  for (int i = 0; i < 10; i++) {

    arg a1 = (arg)malloc(sizeof(struct arg_str));
    a1->q = q;
    a1->f = f;
    strcpy(a1->arg,args[i]);
    if (pthread_create(&threads[i], NULL, thread_add, (void *)a1)) {
      printf("ERROR creating thread %d", i);
      exit(1);
    }
    // printf("%s\n", a1->arg);
  }

  for (int i = 0; i < 3; i++) {
    if (pthread_create(&threads1[i], NULL, thread_get, (void *)q)) {
      printf("ERROR creating thread %d", i);
      exit(1);
    }
  }

  for(int t=0; t < 3; t++) {
       pthread_join(threads1[t], NULL);
  }

  for(int t=0; t < 10; t++) {
       pthread_join(threads[t], NULL);
  }

  return 0;
}
