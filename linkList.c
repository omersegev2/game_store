#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s
{
    int data;
    struct node_s *next;
} node_t;

node_t *create_node(int data)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL)
    {
        printf("Couldn't allocate memory for new_node\n");
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Edge case
node_t *add_node_to_list(node_t *head, int data)
{
    node_t *curr = head;
    node_t *prev = head;

    node_t *new_node = create_node(data);
    if (new_node == NULL)
        return NULL;

    if (head == NULL)
        return new_node;

    if (head->data == data)
    {
        new_node->next = head;
        return new_node;
    }

    while (curr != NULL && curr->data < data)
    {
        prev = curr;
        curr = curr->next;
    }

    new_node->next = prev->next;
    prev->next = new_node;

    return head;
}

// Modify head
void add_node_to_list2(node_t **head, int data)
{
    if (head == NULL)
        return;

    node_t *curr = *head;
    node_t *prev = *head;

    node_t *new_node = create_node(data);
    if (new_node == NULL)
        return;

    // Dealing with special case
    if (*head == NULL || (*head)->data == data)
    {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    while (curr != NULL && curr->data < data)
    {
        prev = curr;
        curr = curr->next;
    }

    new_node->next = prev->next;
    prev->next = new_node;
}

// Fake head element
// All functions xxxx3() deals with fake head element
void add_node_to_list3(node_t *head, int data)
{
    node_t *curr = head->next;
    node_t *prev = head;
    if (head == NULL)
        return;

    node_t *new_node = create_node(data);
    if (new_node == NULL)
        return;

    while (curr != NULL && curr->data < data)
    {
        prev = curr;
        curr = curr->next;
    }

    new_node->next = prev->next;
    prev->next = new_node;
}

void remove_node_from_list3(node_t *head, int data)
{
    if (!head)
        return;

    node_t *curr = head->next;
    node_t *prev = head;

    while (curr)
    {
        if (curr->data == data)
        {
            prev->next = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("not found %d", data);
}

node_t *create_list3()
{
    return create_node(-1);
}

// Note: here we need to destroy head as well
void destroy_list3(node_t *head)
{
    if (!head)
        return;

    node_t *curr = head;
    while (curr)
    {
        head = curr->next;
        free(curr);
        curr = head;
    }
}

void print_list3(node_t *head)
{
    if (!head)
    {
        printf("null\n");
        return;
    }
    node_t *curr = head->next;
    printf("--------------\n");

    while (curr != NULL)
    {
        printf("%d\n", curr->data);
        curr = curr->next;
    }
}

int main()
{

    // Example for calling functions dealing with linked list with a fake node as head

    node_t *head = create_list3();
    if (head == NULL)
        return 1;

    print_list3(head);
    for (int i = 0; i < 10; i++)
    {
        add_node_to_list3(head, i * 10);
    }

    add_node_to_list3(head, 41);
    print_list3(head);

    remove_node_from_list3(head, 41);
    remove_node_from_list3(head, -1);
    print_list3(head);

    remove_node_from_list3(head, 0);
    print_list3(head);

    destroy_list3(head);

    return 0;
}