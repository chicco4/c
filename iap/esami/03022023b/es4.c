#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define a structure for a singly-linked list node
typedef struct list
{
    int data;
    struct list *next;
} list_t;

// Function to append an element to the end of a linked list
void append(list_t **head, int data)
{
    // Allocate memory for a new node
    list_t *new_node = (list_t *)malloc(sizeof(list_t));
    if (new_node == NULL)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    // Set the data and next pointer of the new node
    new_node->data = data;
    new_node->next = NULL;

    // If the list is empty, make the new node the head
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        // Otherwise, traverse the list and add the new node at the end
        list_t *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Function to print the elements of a linked list
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

// Function to check if an element is in a linked list
bool is_in(int x, list_t *l)
{
    while (l)
    {
        if (l->data == x)
            return true;
        l = l->next;
    }
    return false;
}

// Function to filter elements from list 'a' based on list 'b'
list_t *filter(list_t *a, list_t *b)
{
    list_t *new_l = NULL; // Initialize the new filtered list
    list_t *tail = new_l; // Initialize the tail pointer for the new list

    // Iterate through the elements of list 'a'
    while (a)
    {
        // If the current element in 'a' is not in 'b', add it to the filtered list
        if (!is_in(a->data, b))
        {
            // Create a new node for the filtered list
            list_t *new_node = (list_t *)malloc(sizeof(list_t));
            if (!new_node)
                exit(EXIT_FAILURE);

            // Set the data and next pointer of the new node
            new_node->data = a->data;
            new_node->next = NULL;

            // If the filtered list is empty, set both 'new_l' and 'tail' to the new node
            if (new_l == NULL)
                new_l = tail = new_node;
            else
            {
                // Otherwise, add the new node at the end of the filtered list
                tail->next = new_node;
                tail = new_node;
            }
        }
        a = a->next; // Move to the next element in list 'a'
    }
    return new_l; // Return the filtered list
}

int main()
{
    // Create linked lists l1 and l2
    list_t *l1 = NULL;
    list_t *l2 = NULL;

    // Add elements to list 'l1'
    int l1_data[] = {7, 1, 0, 3, 4, 1, 3};
    int l1_length = sizeof(l1_data) / sizeof(l1_data[0]);
    for (int i = 0; i < l1_length; i++)
    {
        append(&l1, l1_data[i]);
    }

    // Add elements to list 'l2'
    int l2_data[] = {1, 3};
    int l2_length = sizeof(l2_data) / sizeof(l2_data[0]);
    for (int i = 0; i < l2_length; i++)
    {
        append(&l2, l2_data[i]);
    }

    // Print lists 'l1' and 'l2'
    printf("l1: ");
    print_list(l1);
    printf("l2: ");
    print_list(l2);

    // Call the filter function to create a new list 'l3'
    list_t *l3 = filter(l1, l2);

    // Print the filtered list 'l3'
    printf("l3: ");
    print_list(l3);

    return 0;
}
