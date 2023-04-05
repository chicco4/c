#ifndef _QUEUE_H_
#define _QUEUE_H_

/** \mainpage Queue
 *
 * This library implements a FIFO Queue.
 *
 */

/**
 * Data type of the elements.
 */
typedef int qdata_t;

/**
 * The FIFO Queue data type
 */
typedef struct queue queue_t;

/**
 * Allocates an empty queue.
 * @return empty queue.
 */
queue_t *q_create();

/**
 * Clones a queue (deep copy)
 * @return vector.
 */
queue_t *q_clone(const queue_t *q);

/**
 * Frees a queue and the memory it uses
 * @param q The queue to be freed.
 */
void q_free(queue_t *q);

/**
 * Prints a queue
 * @param q The queue to be printed.
 */
void q_print(const queue_t *q);

/**
 * Checks if a queue is empty
 * @param q The queue.
 * @return 1 if empty, 0 otherwise
 */
int q_is_empty(const queue_t *q);

/**
 * Returns number of elements in the queue.
 * @param q The queue.
 * @return The number of elements in the queue.
 */
size_t q_size(const queue_t *v);

/**
 * Inserts a new value at the end of the queue.
 * @param q The queue.
 * @param value The value to be inserted.
 */
void q_enqueue(queue_t *q, qdata_t value);

/**
 * Returns the first element of the queue.
 * Program exists if queue is empty.
 * @param q The queue.
 * @return The value in the first position of the queue.
 */
qdata_t q_dequeue(queue_t *q);

#endif