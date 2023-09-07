#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    int data;
    struct list *next;
} list_t;

// Funzione per inserire un nuovo nodo in testa alla lista
list_t *insert(list_t *head, int data)
{
    list_t *new_node = (list_t *)malloc(sizeof(list_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Errore di allocazione della memoria.\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = head;
    return new_node;
}

// Funzione per cercare se un elemento esiste nella lista
int exists(list_t *head, int data)
{
    list_t *current = head;
    while (current != NULL)
    {
        if (current->data == data)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Funzione per rimuovere tutti gli elementi dalla lista tranne quelli che appaiono almeno due volte
list_t *dups(list_t *l)
{
    if (l == NULL)
    {
        return NULL;
    }

    list_t *result = NULL;
    list_t *current = l;

    while (current != NULL)
    {
        if (exists(current->next, current->data) && !exists(result, current->data))
        {
            result = insert(result, current->data);
        }
        current = current->next;
    }

    return result;
}

// Funzione per stampare una lista
void print_list(list_t *head)
{
    list_t *current = head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Funzione per liberare la memoria allocata per una lista
void free_list(list_t *head)
{
    list_t *current = head;
    while (current != NULL)
    {
        list_t *temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    list_t *l1 = NULL;
    l1 = insert(l1, 1);
    l1 = insert(l1, 1);
    l1 = insert(l1, 2);
    l1 = insert(l1, 3);
    l1 = insert(l1, 1);
    l1 = insert(l1, 2);
    l1 = insert(l1, 4);

    list_t *l2 = dups(l1);

    printf("l1 = ");
    print_list(l1);

    printf("l2 = ");
    print_list(l2);

    free_list(l1);
    free_list(l2);

    return 0;
}
