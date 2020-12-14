#include <stdio.h>
#include <wchar.h>
#include <time.h>

#include "arr_queue.h"
#include "errors.h"
#include "my_functions.h"

int aq_pop(arr_queue_t *queue, order_t *const order)
{
    if (!queue->length)
        return ERR_EMPTY_QUEUE;

    queue->length--;
    *order = queue->array[queue->out];
    queue->out = (queue->out + 1 + MAX_ARR_LEN) % MAX_ARR_LEN;
    return OK;
}

int aq_push(arr_queue_t *queue, const order_t order)
{
    if (queue->length == MAX_ARR_LEN)
        return ERR_FULL_QUEUE;

    queue->array[queue->in] = order;
    queue->in = (queue->in + 1 + MAX_ARR_LEN) % MAX_ARR_LEN;
    queue->length++;
    return OK;
}

int aq_print(arr_queue_t *queue)
{
    if (!queue->length)
        return ERR_EMPTY_QUEUE;

    arr_queue_t tmp = { .length = 0 };
    while (queue->length)
    {
        fwprintf(stdout, L"%p\n", queue->array + queue->out);
        order_t el;
        aq_pop(queue, &el);
        aq_push(&tmp, el);
    }

    while (tmp.length)
    {
        order_t el;
        aq_pop(&tmp, &el);
        aq_push(queue, el);
    }

    fwprintf(stdout, L"\nПамять (байт): %ld\n", sizeof(*queue));
        
    return OK;
}

int aq_pops(arr_queue_t *queue)
{
    uint num;
    putws(L"\nВведите количество удаляемых элементов:\n");
    int exit_code = read_uint(&num);
    wclear_stdin();

    if (!exit_code && (num > queue->length))
        exit_code = ERR_INVALID_NUM;

    if (!exit_code)
    {
        order_t el;
        clock_t start, time;
        start = clock();

        while (num--)
            aq_pop(queue, &el);

        time = clock() - start;

        putws(L"Все элементы успешно удалены!\n");
        fwprintf(stdout, L"Время удаления элемент(a/ов) (в тактах): %ld\n", time);
    }

    return exit_code;
}

int aq_pushs(arr_queue_t *queue)
{
    uint num;
    putws(L"\nВведите количество добавляемых элементов:\n");
    int exit_code = read_uint(&num);
    wclear_stdin();

    if (!exit_code && (num > MAX_ARR_LEN - queue->length))
        exit_code = ERR_INVALID_NUM;

    if (!exit_code)
    {
        order_t el = { .type = FIRST, .coming = 0, .processing = 0 };
        clock_t start, finish, time;
        start = clock();

        while (num--)
            aq_push(queue, el);

        finish = clock();

        time = finish - start;

        putws(L"Все элементы успешно добавлены!\n");
        fwprintf(stdout, L"Время добавления элемент(a/ов) (в тактах): %ld\n", time);
    }

    return exit_code;
}
