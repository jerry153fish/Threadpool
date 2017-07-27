/**********************************
 * @author   Jerry Chen
 * Date:     27 Jul 17
 * Email:    jerry153fish@gmail.com
 **********************************/

#ifndef J_QUEUE_H
#define J_QUEUE_H
#ifdef __cplusplus
extern "C" {
#endif

// max queue size
#define MAX_QUEUE_SIZE 2000
// struct queue
struct j_queue_str;
typedef struct j_queue_str *j_queue;
// init
j_queue q_init();
// put
void q_put(j_queue q, void *fn, void *arg);
// get
void *q_get(j_queue q);
// destroy
void destroy_q(j_queue q);
void print_q(j_queue q);

#ifdef __cplusplus
}
#endif
#endif
