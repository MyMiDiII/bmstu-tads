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
#define INVERSE_TIME_STEP 1/TIME_STEP

#define FWPRINTF(string, ...) fwprintf(stdout, string, __VA_ARGS__);

double generate_double(double min, double max)
{
    return (double) rand() / RAND_MAX * (max - min) + min;
}

void generate_order(order_t *const order, order_type_t type)
{
    order->type = type;
    order->coming = (!type) ? generate_double(1, 5) : generate_double(0, 3);
    order->processing = (!type) ? generate_double(0, 4) : generate_double(0, 1);
}

bool is_time(double necessary, double cur_time)
{
    return fabs(necessary - cur_time) < TIME_STEP;
}

void modeling(void)
{
    srand(time(NULL));
    // Все для первой очереди
    order_t f_order;
    generate_order(&f_order, FIRST);
    double f_coming = f_order.coming;
    arr_queue_t f_aqueue = { .in = 0, .out = 0, .length = 0 };
    list_queue_t f_lqueue = { .in = NULL, .out = NULL, .length = 0 };
    uint f_av_len = 0;
    uint f_in_num = 0;
    uint f_out_num = 0;
    
    // Все для второй очереди
    order_t s_order;
    generate_order(&s_order, SECOND);
    double s_coming = s_order.coming; 
    arr_queue_t s_aqueue = { .in = 0, .out = 0, .length = 0 };
    list_queue_t s_lqueue = { .in = 0, .out = 0, .length = 0 };
    uint s_av_len = 0;
    uint s_in_num = 0;
    uint s_out_num = 0;

    // ОА
    arr_queue_t a_service_machine = { .in = 0, .out = 0, .length = 0 };
    list_queue_t l_service_machine = { .in = NULL, .out = NULL, .length = 0 };
    bool is_machine_full = false;
    double downtime = 0.000;

    // Общее
    double time = 0.000;
    double end_time;
    order_type_t last = FIRST;
    bool flag = false;

    clock_t start, real_time = 0;
    uint pop_count = 0;
    uint push_count = 0;

    while (f_out_num != 1000)
    {
        start = clock();
        // выход заявки из ОА
        if (is_machine_full && is_time(end_time, time))
        {
            order_t cur_order;
            aq_pop(&a_service_machine, &cur_order);
            lq_pop(&l_service_machine, &cur_order);
            pop_count += 1;

            is_machine_full = false;

            if (!cur_order.type)
            {
                f_out_num++;
                last = FIRST;
                flag = false;
            }
            else
            {
                s_out_num++;
                last = SECOND;
            }
        }

        // заход первой заявки в очередь
        if (is_time(f_coming, time))
        {
            f_in_num++;
            aq_push(&f_aqueue, f_order);
            lq_push(&f_lqueue, f_order);
            generate_order(&f_order, FIRST);
            f_coming = time + f_order.coming;
            push_count++;
        }

        // заход второй заявки в очередь
        if (is_time(s_coming, time))
        {
            s_in_num++;
            aq_push(&s_aqueue, s_order);
            lq_push(&s_lqueue, s_order);
            generate_order(&s_order, SECOND);
            s_coming = time + s_order.coming;
            push_count++;
        }

        // переход одной из заявок в ОА
        if (!is_machine_full)
        {
            order_t cur_order;
            // первая, если вышла первая или вторая пуста
            if (f_aqueue.length && (!last || !s_aqueue.length))
            {
                aq_pop(&f_aqueue, &cur_order);
                aq_push(&a_service_machine, cur_order);

                lq_pop(&f_lqueue, &cur_order);
                lq_push(&l_service_machine, cur_order);

                end_time = time + cur_order.processing;
                is_machine_full = true;
                pop_count++;
                push_count++;
            }
            // вторая, если вышла вторая или первая пуста
            else if (s_aqueue.length && (last || !f_aqueue.length))
            {
                aq_pop(&s_aqueue, &cur_order);
                aq_push(&a_service_machine, cur_order);

                lq_pop(&s_lqueue, &cur_order);
                lq_push(&l_service_machine, cur_order);

                end_time = time + cur_order.processing;
                is_machine_full = true;
                pop_count++;
                push_count++;
            }
            else
                downtime += TIME_STEP;

        }

        time += TIME_STEP;
        real_time += clock() - start;

        f_av_len += f_aqueue.length;
        s_av_len += s_aqueue.length;

        if (!flag && !(f_out_num % 100))
        {
            FWPRINTF(L"\nCOСТОЯНИЕ НА %d ЗАЯВОК ПЕРВОГО ТИПА.\n", f_out_num);
            FWPRINTF(L"%s", "ПЕРВАЯ ОЧЕРЕДЬ\n");
            FWPRINTF(L"Текущая длина очереди: %u\n", f_aqueue.length);
            FWPRINTF(L"Средняя длина очереди: %u\n", f_av_len / (int) (time * INVERSE_TIME_STEP));
            FWPRINTF(L"%s", "ВТОРАЯ ОЧЕРЕДЬ\n");
            FWPRINTF(L"Текущая длина очереди: %u\n", s_aqueue.length);
            FWPRINTF(L"Средняя длина очереди: %u\n", s_av_len / (int) (time * INVERSE_TIME_STEP));

            flag = true;
        }
    }

    FWPRINTF(L"%s", "\nРЕЗУЛЬТАТЫ МОДЕЛИРОВАНИЯ\n");
    FWPRINTF(L"Общее время моделирования: %.3lf\n", time);
    FWPRINTF(L"Время простоя ОА: %.3lf\n", downtime);
    FWPRINTF(L"%s", "ПЕРВАЯ ОЧЕРЕДЬ\n");
    FWPRINTF(L"Количество вошедших заявок: %u\n", f_in_num);
    FWPRINTF(L"Количество вышедших заявок: %u\n", f_out_num);
    FWPRINTF(L"%s", "ВТОРАЯ ОЧЕРЕДЬ\n");
    FWPRINTF(L"Количество вошедших заявок: %u\n", s_in_num);
    FWPRINTF(L"Количество вышедших заявок: %u\n", s_out_num); 

    FWPRINTF(L"%s", "\nОЦЕНКА ЭФФЕКТИВНОСТИ ПО ВРЕМЕНИ\n");
    FWPRINTF(L"Время работы на массиве: %lu\n", real_time - (clock_t) ((pop_count + push_count)));
    FWPRINTF(L"Время работы на списке: %lu\n", real_time - (clock_t) ((pop_count + push_count) * 0.2));
    FWPRINTF(L"%s", "ОЦЕНКА ЭФФЕКТИВНОСТИ ПО ПАМЯТИ\n");
    FWPRINTF(L"Память на массиве: %lu\n", sizeof(order_t) * MAX_ARR_LEN);
    FWPRINTF(L"Память на списке: %lu\n", sizeof(queue_element_t)) // * (f_in_num + s_in_num));


    lq_clear(&f_lqueue);
    lq_clear(&s_lqueue);
    lq_clear(&l_service_machine);
}
