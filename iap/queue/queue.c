#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/** List node data type. */
typedef struct node
{

    /** Stored element */

    qdata_t data;

    /** Pointer to the next node in the list */

    struct node *next;
} node_t;

/**
 * The FIFO Queue data type
 */
struct queue
{

    /** The number of elements in the queue */

    size_t size;

    /** The first element in the queue */

    node_t *head;

    /** The last element in the queue */

    node_t *tail;
};

/**
 * Fatal exit if the given queue is empty.
 * @param q The queue.
 */
void _q_check_non_empty(const queue_t *q)
{

    if (q_is_empty(q))
    {

        printf("Error: Empty queue\n");

        exit(EXIT_FAILURE);
    }
}

queue_t *q_create()
{

    queue_t *q = (queue_t *)malloc(sizeof(queue_t));

    q->size = 0;

    q->head = q->tail = NULL;

    return q;
}

queue_t *q_clone(const queue_t *q)
{

    queue_t *c = q_create();

    node_t *n = q->head;

    while (n != NULL)
    {

        q_enqueue(c, n->data);

        n = n->next;
    }

    return c;
}

void q_free(queue_t *q)
{

    node_t *n = q->head;

    while (n != NULL)
    {

        struct node *aux = n->next;

        free(n);

        n = aux;
    }

    free(q);
}

void q_print(const queue_t *q)
{

    node_t *n = q->head;

    printf("< ");

    while (n != NULL)
    {

        printf("%d ", (int)n->data);

        n = n->next;
    }

    printf(">");
}

int q_is_empty(const queue_t *q)
{

    return q->size == 0;
}

size_t q_size(const queue_t *q)
{

    return q->size;
}

void q_enqueue(queue_t *q, qdata_t value)
{

    node_t *n = (node_t *)malloc(sizeof(node_t));

    n->data = value;

    n->next = NULL;

    if (q_is_empty(q))
    {

        q->head = q->tail = n;
    }
    else
    {

        q->tail->next = n;

        q->tail = n;
    }

    q->size++;
}

qdata_t q_dequeue(queue_t *q)
{

    node_t *n;

    qdata_t v;

    _q_check_non_empty(q);

    n = q->head;

    if (q->size == 1) /* only one element left */

        q->head = q->tail = NULL;

    else

        q->head = q->head->next;

    q->size--;

    v = n->data;

    free(n);

    return v;
}