#ifndef __LIST_QUEUE_H__

#define __LIST_QUEUE_H__

#include "order.h"
#include "my_functions.h"

#define MAX_LIST_LEN 10000

typedef struct queue_element queue_element_t;

struct queue_element
{
    order_t data;
    queue_element_t *prev;
};

typedef struct list_queue
{
    queue_element_t *in;
    queue_element_t *out;
    uint length;
} list_queue_t;

int lq_pop(list_queue_t *queue, order_t *const order);

int lq_push(list_queue_t *queue, const order_t order);

int lq_print(list_queue_t *queue);

int lq_pushs(list_queue_t *queue);

int lq_pops(list_queue_t *queue);

int lq_clear(list_queue_t *queue);

#endif
