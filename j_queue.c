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

// struct queue
struct j_queue_str {
  job front;
  job rear;
  pthread_mutex_t lock; // queue lock
  pthread_cond_t  cond_not_full; // not full signal for put
  pthread_cond_t  cond_not_empty; // not empty signal for get
  int size;
};
// init
j_queue q_init() {
  j_queue q;
  if ((q = (j_queue)malloc(sizeof(struct j_queue_str))) != NULL) {
    q->size = 0;
    q->front = NULL;
    q->rear = NULL;
    if (pthread_mutex_init(&q->lock, NULL) != 0) {
      free(q);
      return NULL;
    }
    if (pthread_cond_init(&q->cond_not_full, NULL) != 0) {
      free(q);
      return NULL;
    }
    if (pthread_cond_init(&q->cond_not_empty, NULL) != 0) {
      free(q);
      return NULL;
    }
  } else {
    return NULL;
  }
  return q;
};
// put
void q_put(j_queue q, void *func, void *arg) {
  pthread_mutex_lock(&q->lock);
  // if full wait for not full sigal and hait and release the mutex
  while(q->size == MAX_QUEUE_SIZE) {
    pthread_cond_wait(&q->cond_not_full, &q->lock);
  }
  fn f = (fn)func;
  job j = job_init(f, arg);
  switch(q->size) {
    // empty queue
    case 0:
      q->size++;
      q->front = j;
      q->rear = j;
      break;
    // other
    default:
      q->size++;
      setNextJob(q->rear, j);
      q->rear = j;
      break;
  }
  pthread_cond_signal(&q->cond_not_empty);
  pthread_mutex_unlock(&q->lock);
};
// get
void *q_get(j_queue q) {
  pthread_mutex_lock(&q->lock);
  // if empty wait for not empty sigal and hait and release the mutex
  while(q->size == 0) {
    pthread_cond_wait(&q->cond_not_empty, &q->lock);
  }
  // get next job
  job re = q->front;
  switch(q->size) {
    // one left in the queue
    case 1:
      q->size = 0;
      q->front = NULL;
      q->rear = NULL;
      break;
    default:
      q->size--;
      q->front = getNextJob(q->front);
      break;
  }
  pthread_cond_signal(&q->cond_not_full);
  pthread_mutex_unlock(&q->lock);
  setNextJob(re, NULL);
  return re;
};
// destroy
void destroy_q(j_queue q) {
  while(q->front) {
    destroy_job(q->front);
    q->front = getNextJob(q->front);
  }
  free(q);
};
