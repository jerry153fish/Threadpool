/**********************************
 * @author   Jerry Chen
 * Date:     27 Jul 17
 * Email:    jerry153fish@gmail.com
 **********************************/
#ifdef THREADPOOL_H
#define THREADPOOL_H
#ifdef __cplusplus
extern "C" {
#endif
// max pool size
#define MAX_POOL_NUM 10

// simple declare universal struct
struct thpool_s;
typedef thpool_s *threadpool;

// simple declare a point ot function return void
typedef void (*pool_fn)(void *);

// threadpool create
threadpool threadpool_init(int thread_size);

// add function to pool
int pool_add_fn(threadpool pool, pool_fn fn, void *arg);
// destroy
int pool_destroy(threadpool pool);

#ifdef __cplusplus
}
#endi
#endif
