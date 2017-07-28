/**********************************
 * @author   Jerry Chen
 * Date:     27 Jul 17
 * Email:    jerry153fish@gmail.com
 **********************************/
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
struct thpool_s {
  j_queue q;
  pthread_t *threads;
  int thread_size;
};

void *thread_fn(void *arg) {
  threadpool tp = (threadpool)arg;
  j_queue q = tp->q;
  while(pool_alive) {
    job j = q_get(q);
    run_job(j);
  }
};
// threadpool create
threadpool threadpool_init(int thread_size) {
  threadpool tp = (threadpool)malloc(sizeof(struct thpool_s));
  tp->q = q_init();
  tp->thread_size = thread_size;
  tp->threads = malloc(sizeof(pthread_t)*thread_size);
  pool_alive = 1;
  for (int i = 0; i < thread_size; i++) {
    if (pthread_create(&tp->threads[i], NULL, thread_fn, (void *)tp)) {
      printf("ERROR creating thread %d", i);
      exit(1);
    }
  }
  return tp;
};

// add function to pool
void pool_add_fn(threadpool tp, pool_fn fn, void *arg) {
  q_put(tp->q, fn, arg);
};
// destroy
void pool_destroy(threadpool tp) {
  pool_alive = 0;
  destroy_q(tp->q);
  free(tp);
};
