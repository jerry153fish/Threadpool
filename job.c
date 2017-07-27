/**********************************
 * @author   Jerry Chen
 * Date:     27 Jul 17
 * Email:    jerry153fish@gmail.com
 **********************************/
#include <stdio.h>
#include <stdlib.h>
#include "job.h"

//job struct
struct job_str {
  fn fn;
  void *arg;
  job next;
};
// init
job job_init(fn f, void *arg) {
  job j = (job)malloc(sizeof(struct job_str));
  j->fn = f;
  j->arg = arg;
  return j;
};
// destroy_job
void destroy_job(job j) {
  free(j);
};
// run
void run_job(job j) {
  j->fn(j->arg);
  destroy_job(j);
};
// getter
job getNextJob(job j) {
  return j->next;
};
// setter
void setNextJob(job j, job n) {
  j->next = n;
}
