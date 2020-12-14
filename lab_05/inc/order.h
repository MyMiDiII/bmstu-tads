#ifndef __ORDER_H__

#define __ORDER_H__

#include <stdio.h>

typedef enum order_type
{
    FIRST,
    SECOND
} order_type_t;

typedef struct order
{
    order_type_t type;
    double coming;
    double processing;
} order_t;

#endif
