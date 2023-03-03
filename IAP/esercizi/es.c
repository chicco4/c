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

node_t *estract_at(node_t **l, size_t pos)
{
    int i = 0;
    node_t *retval;

    node_t *current = *l;

    if (pos == 0)
    {
        return *l;
    }

    for (i = 0; i < pos; i++)
    {
        current = current->next;
    }

    return current;
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

    node_t *new_list = estract_at(&list, 3);

    print_list(new_list);

    return 0;
}