#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <time.h>

#include "list_queue.h"
#include "errors.h"
#include "order.h"
#include "my_functions.h"

int lq_pop(list_queue_t *queue, order_t *const order)
{
    if (!queue)
        return ERR_NULL_POINTER;

    if (!queue->length || !queue->in || !queue->out)
        return ERR_EMPTY_QUEUE;

    queue_element_t *tmp = queue->out;
    queue->out = tmp->prev;
    queue->in = (!queue->out) ? NULL : queue->in;
    queue->length--;

    *order = tmp->data;
    free(tmp);
    return OK;
}

int lq_push(list_queue_t *queue, const order_t order)
{
    if (!queue)
        return ERR_NULL_POINTER;
    
    if (queue->length >= MAX_LIST_LEN)
        return ERR_FULL_QUEUE;

    queue_element_t *new = malloc(sizeof(queue_element_t));

    if (!new)
        return ERR_MEMORY;

    new->data = order;
    new->prev = NULL;

    (!queue->in) ? (queue->in = new) : ((*queue->in).prev = new);
    queue->in = new;
    queue->out = (!queue->out) ? new : queue->out;
    queue->length++;

    return OK;
}

int lq_print(list_queue_t *queue)
{
    if (!queue)
        return ERR_EMPTY_QUEUE;

    list_queue_t tmp = { .in = NULL, .length = 0, .out = 0 };
    while (queue->length)
    {
        fwprintf(stdout, L"%p\n", (void *) queue->out);

        order_t el;
        lq_pop(queue, &el);
        lq_push(&tmp, el);
    }

    while (tmp.length)
    {
        order_t el;
        lq_pop(&tmp, &el);
        lq_push(queue, el);
    }

    fwprintf(stdout, L"\nПамять (байт): %ld\n",
             sizeof(list_queue_t) * queue->length);

    return OK;
}

int lq_pops(list_queue_t *queue)
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
            lq_pop(queue, &el);

        time = clock() - start;

        putws(L"Все элементы успешно удалены!\n");
        fwprintf(stdout, L"Время удаления элемент(a/ов) (в тактах): %ld\n", time);
    }

    return exit_code;
}

int lq_pushs(list_queue_t *queue)
{
    uint num;
    putws(L"\nВведите количество добавляемых элементов:\n");
    int exit_code = read_uint(&num);
    wclear_stdin();

    if (!exit_code && (num > MAX_LIST_LEN - queue->length))
        exit_code = ERR_INVALID_NUM;

    if (!exit_code)
    {
        order_t el = { .type = FIRST, .coming = 0, .processing = 0 };
        clock_t start, time;
        start = clock();

        while (num--)
            lq_push(queue, el);

        time = clock() - start;

        putws(L"Все элементы успешно добавлены!\n");
        fwprintf(stdout, L"Время добавления элемент(a/ов) (в тактах): %ld\n", time);
    }

    return exit_code;
}

int lq_clear(list_queue_t *queue)
{
    int exit_code = OK;
    order_t el;

    while (!exit_code && queue->length)
       exit_code = lq_pop(queue, &el);

    return exit_code;
}
