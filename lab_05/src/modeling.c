#include <wchar.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "modeling.h"
#include "my_functions.h"
#include "order.h"
#include "arr_queue.h"
#include "list_queue.h"

#define TIME_STEP 1e-3

double generate_double(double min, double max)
{
    return (double) rand() / RAND_MAX * (max - min) + min;
}

void generate_order(order_t *const order, order_type_t type)
{
    order->type = type;
    order->coming = (!type) ? generate_double(1, 5) : generate_double(0, 3);
    order->processing = (!type) ? generate_double(0, 4) : generate_double(0, 1);
    //order->coming = 0.010;
    //order->processing = 0.020;
}

bool is_time(double necessary, double cur_time)
{
    // fwprintf(stdout, L"is_time_fabs = %lf\n", fabs(necessary - cur_time));
    // fwprintf(stdout, L"is_time = %d\n", fabs(necessary - cur_time) < TIME_STEP);
    return fabs(necessary - cur_time) < TIME_STEP;
}

void modeling(void)
{
    // сделать одну очередь
    // добавить вторую
    //
    // Все для первой очереди
    uint num_first = 0;
    order_t f_order; // , s_order;
    generate_order(&f_order, FIRST);
    double f_prev_coming = 0.000;
    arr_queue_t f_aqueue = { .in = 0, .out = 0, .length = 0 };
    list_queue_t f_lqueue = { .in = NULL, .out = NULL, .length = 0 };
    
    // Все для второй очереди
    // order_t s_order;
    // uint num_second = 0;
    // generate_order(&s_order, SECOND);
    // double s_prev_coming = 0.000; 

    // Общее
    double time = 1.000;
    arr_queue_t a_service_machine = { .in = 0, .out = 0, .length = 0 };
    list_queue_t l_service_machine = { .in = NULL, .out = NULL, .length = 0 };
    bool is_machine_full = false;
    double begin_time = 0.000;

    fwprintf(stdout, L"order_coming = %lf\n", f_order.coming);
    fwprintf(stdout, L"order_processing = %lf\n", f_order.processing);

    while (num_first != 1000)
    {
        // putws(L"\n");
        // fwprintf(stdout, L"is_machine_full = %d\n", is_machine_full);

        // if (is_machine_full)
        //     fwprintf(stdout, L"nec_time  = %lf\n", 
        //              a_service_machine.array[a_service_machine.out].processing);

        // fwprintf(stdout, L"time  = %lf\n", time);

        if (is_machine_full && is_time(begin_time + 
            a_service_machine.array[a_service_machine.out].processing, time))
        {
            order_t cur_order;
            aq_pop(&a_service_machine, &cur_order);
            lq_pop(&l_service_machine, &cur_order);
            is_machine_full = false;
            num_first++;
            putws(L"OK\n");
        }

        // fwprintf(stdout, L"time_coming  = %lf\n", f_prev_coming + f_order.coming);
        // fwprintf(stdout, L"is_time  = %d\n", is_time(f_prev_coming + f_order.coming, time));

        if (is_time(f_prev_coming + f_order.coming, time))
        {
            // fwprintf(stdout, L"proc = %lf\n", f_order.processing);
            // fwprintf(stdout, L"coming = %lf\n", f_order.coming);
            // fwprintf(stdout, L"type = %d\n", f_order.type);
            aq_push(&f_aqueue, f_order);
            lq_push(&f_lqueue, f_order);
            
            // order_t cur_order;
            // lq_pop(&f_lqueue, &cur_order);
            // fwprintf(stdout, L"proc = %lf\n", cur_order.processing);
            // fwprintf(stdout, L"coming = %lf\n", cur_order.coming);
            // fwprintf(stdout, L"type = %d\n", cur_order.type);

            generate_order(&f_order, FIRST);
            f_prev_coming = time;
        }

        if (!a_service_machine.length && f_aqueue.length)
        {
            order_t cur_order;
            aq_pop(&f_aqueue, &cur_order);
            aq_push(&a_service_machine, cur_order);

            // fwprintf(stdout, L"proc = %lf\n", cur_order.processing);

            lq_pop(&f_lqueue, &cur_order);
            lq_push(&l_service_machine, cur_order);

            begin_time = time;
            is_machine_full = true;
        }

        time += TIME_STEP;

        //fwprintf(stdout, L"lena1 = %u\n", f_aqueue.length);
        //fwprintf(stdout, L"lenl1 = %u\n", f_lqueue.length);
    }

    fwprintf(stdout, L"time = %lf\n", time);
}
