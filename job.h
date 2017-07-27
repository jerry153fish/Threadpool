/**********************************
 * @author   Jerry Chen
 * Date:     27 Jul 17
 * Email:    jerry153fish@gmail.com
 **********************************/
#ifndef JOB_H
#define JOB_H
#ifdef __cplusplus
extern "C" {
#endif
// universal void function
typedef void (*fn)(void *arg);
struct job_str;
typedef struct job_str *job;

// Init
job job_init(fn f, void *arg);
//run
void run_job(job b);
//destroy
void destroy_job(job b);
// getter & setter
job getNextJob(job j);

void setNextJob(job j, job n);

#ifdef __cplusplus
}
#endif
#endif
