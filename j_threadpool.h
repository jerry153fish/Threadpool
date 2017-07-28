/**********************************
 * @author   Jerry Chen
 * Date:     27 Jul 17
 * Email:    jerry153fish@gmail.com
 **********************************/
#ifndef J_THREADPOOL_H
#define J_THREADPOOL_H
#ifdef __cplusplus
extern "C" {
#endif
// max pool size
#define MAX_POOL_NUM 10

// simple declare universal struct
struct thpool_s;
typedef struct thpool_s *threadpool;

// simple declare a point ot function return void
typedef void (*pool_fn)(void *);

// threadpool create
threadpool threadpool_init(int thread_size);

// add function to pool
void pool_add_fn(threadpool tp, pool_fn fn, void *arg);
// destroy
void pool_destroy(threadpool tp);

#ifdef __cplusplus
}
#endif
#endif
