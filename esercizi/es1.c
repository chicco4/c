#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
} node_t;

void print_list(node_t *head)
{
    node_t *current = head;

    while (current != NULL)
    {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

node_t *create(int val)
{
    node_t *l = malloc(sizeof(node_t));
    l->val = val;
    return l;
}

void push_end(node_t *head, int val)
{
    node_t *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = (node_t *)malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

/*--------------*/

node_t *extract_at(node_t **l, size_t pos)
{
    node_t *current = *l;
    node_t *retval = NULL;

    if (pos == 0)
    {
        node_t *next_node = (*l)->next;
        retval = (*l);
        *l = next_node;
        return retval;
    }

    // ottengo il nodo prima
    for (size_t i = 0; i < pos - 1; i++)
    {
        current = current->next;
    }

    // tolgo il nodo in mezzo
    retval = current->next;
    current->next = retval->next;

    // tolgo il next a retval
    retval->next = NULL;

    return retval;
}

int main(void)
{
    system("clear");

    node_t *list = create(0);

    for (size_t i = 1; i < 10; i++)
    {
        push_end(list, i);
    }

    print_list(list);

    node_t *node = extract_at(&list, 2);

    printf("%d\n", node->val);
    print_list(list);

    return 0;
}