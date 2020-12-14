#ifndef __ARR_QUEUE_H__

#define __ARR_QUEUE_H__

#include "order.h"
#include "my_functions.h"

#define MAX_ARR_LEN 2000

typedef struct
{
    order_t array[MAX_ARR_LEN];
    uint length;
    uint in;
    uint out;
} arr_queue_t;

int aq_pop(arr_queue_t *queue, order_t *const order);

int aq_push(arr_queue_t *queue, const order_t order);

int aq_print(arr_queue_t *queue);

int aq_pushs(arr_queue_t *queue);

int aq_pops(arr_queue_t *queue);

#endif
