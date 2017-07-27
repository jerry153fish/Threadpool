/**********************************
 * @author   Jerry Chen
 * Date:     27 Jul 17
 * Email:    jerry153fish@gmail.com
 **********************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "j_queue.h"
#include "job.h"
#include "threadpool.h"
// simple declare universal struct
struct thpool_s {
  j_queue q;
  int thread_size;
}

// threadpool create
threadpool threadpool_init(int thread_size);

// add function to pool
int pool_add_fn(threadpool pool, pool_fn fn, void *arg);
// destroy
int pool_destroy(threadpool pool);
