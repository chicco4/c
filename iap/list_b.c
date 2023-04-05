#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_node
{
    int data;
    struct list_node *next;
} list_node_t;

typedef struct
{
    list_node_t *head;
} list_t;

list_t *list_create(list_node_t *n)
{
    list_t *l = malloc(sizeof(list_t));
    l->head = n;
    return l;
}

list_t *list_empty()
{
    return list_create(NULL);
}

list_node_t *list_node_create(int x)
{
    list_node_t *n = (list_node_t *)malloc(sizeof(list_node_t));
    n->data = x;
    n->next = NULL;
    return n;
}

list_t *list_create_singleton(int x)
{
    return list_create(list_node_create(x));
}

list_node_t *list_node_last(list_node_t *n)
{
    return n && n->next ? list_node_last(n->next) : n;
}

list_node_t *list_last(list_t *l)
{
    return list_node_last(l->head);
}

void list_node_print(const list_node_t *n)
{
    if (n)
    {
        printf("%d ", n->data);
        list_node_print(n->next);
    }
}

void list_print(const list_t *l)
{
    printf("[ ");
    list_node_print(l->head);
    printf("]\n");
}

list_node_t *array_to_list_node(int *a, size_t len)
{
    if (len == 0)
        return NULL;
    else
    {
        list_node_t *n = malloc(sizeof(list_node_t));
        n->data = *a;
        n->next = array_to_list_node(a + 1, len - 1);
        return n;
    }
}

list_t *array_to_list(int *a, size_t len)
{
    list_t *l = malloc(sizeof(list_t));
    l->head = array_to_list_node(a, len);
    return l;
}

void list_node_free(list_node_t *n)
{
    if (n)
    {
        list_node_free(n->next);
        free(n); /* libera la memoria di QUESTO nodo al RITORNO dalla ricorsione*/
    }
}

void list_free(list_t *l)
{
    list_node_free(l->head);
    free(l);
}

size_t list_node_size(const list_node_t *l)
{
    if (l == NULL)
        return 0;
    else
        return 1 + list_node_size(l->next);
}

size_t list_size(const list_t *l)
{
    return list_node_size(l->head);
}

list_node_t *__list_node_search(list_node_t *n, int v, size_t *pos, size_t i)
{
    if (n)
    {
        if (n->data == v)
        {
            *pos = i;
            return n;
        }
        return __list_node_search(n->next, v, pos, i + 1);
    }
    *pos = -1;
    return NULL;
}

list_node_t *list_node_search(list_node_t *n, int v, size_t *pos)
{
    return __list_node_search(n, v, pos, 0);
}

list_node_t *list_search(list_t *l, int v, size_t *pos)
{
    return list_node_search(l->head, v, pos);
}

int list_node_is_prefix(const list_node_t *n1, const list_node_t *n2)
{
    if (n1 && n2 && n1->data == n2->data)
        return list_node_is_prefix(n1->next, n2->next);
    return n2 == NULL;
}

int list_is_prefix(const list_t *l1, const list_t *l2)
{
    return list_node_is_prefix(l1->head, l2->head);
}

list_node_t *__list_node_contains_sublist(list_node_t *n1, list_node_t *n2, size_t *pos, size_t i)
{
    if (n1)
    {
        if (list_node_is_prefix(n1, n2))
        {
            *pos = i;
            return n1;
        }
        return __list_node_contains_sublist(n1->next, n2, pos, i + 1);
    }
    *pos = -1;
    return NULL;
}

list_node_t *list_node_contains_sublist(list_node_t *n1, list_node_t *n2, size_t *pos)
{
    return __list_node_contains_sublist(n1, n2, pos, 0);
}

list_node_t *list_contains_sublist(list_t *l1, list_t *l2, size_t *res)
{
    return list_node_contains_sublist(l1->head, l2->head, res);
}

list_node_t *list_node_search_last(list_node_t *l, int n, size_t *pos)
{
    if (l)
    {
        size_t pos1;
        list_node_t *r = list_node_search_last(l->next, n, &pos1);
        if (r)
        {
            /* un'occorrenza è stata trovata */
            *pos = pos1 + 1; /* +1 per contare il nodo corrente */
            return r;
        }
        else
        {
            /* se non è stata trovata ma è presente in questo nodo ritorno la posizione */
            if (l->data == n)
            {
                *pos = 0;
                return l;
            }

            else
            {
                *pos = pos1;
                return r;
            }
        }
    }
    *pos = -1;
    return NULL;
}

list_node_t *list_search_last(list_t *l, int n, size_t *pos)
{
    return list_node_search_last(l->head, n, pos);
}

list_node_t *list_node_remove_all(list_node_t *l, int n)
{
    list_node_t *tmp;
    /* caso base */
    if (l == NULL)
        return l;
    /* passo ricorsivo */
    l->next = list_node_remove_all(l->next, n);
    /* se il nodo corrente contiene, n, elimina il nodo */
    if (l->data == n)
    {
        tmp = l;
        l = l->next;
        free(tmp);
    }
    return l;
}

void list_remove_all(list_t *l, int n)
{
    l->head = list_node_remove_all(l->head, n);
}

list_node_t *list_node_unique(const list_node_t *l)
{
    list_node_t *new_n, *new_l;
    size_t pos;
    /* caso base */
    if (l == NULL)
        return NULL;
    /* passo ricorsivo */
    new_l = list_node_unique(l->next);
    /* utilizza la funzione last_pos definita sopra.
     * Se ritorna -1 l'elemento non è presente nel
     * resto della lista, e quindi va tenuto. */
    if (!list_node_search_last(l->next, l->data, &pos))
    {
        /* crea il nodo con il valore di l->data */
        new_n = list_node_create(l->data);
        new_n->next = new_l;
        new_l = new_n;
    }
    return new_l;
}

list_t *list_unique(const list_t *l)
{
    return list_create(list_node_unique(l->head));
}

int main()
{
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    list_t *l = array_to_list(a, sizeof(a) / sizeof(int));

    list_print(l);
    return 0;
}