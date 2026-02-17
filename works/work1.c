#include "work.h"

static int help_selected(const char *selected);
static void to_uppercase_inplace(char *text);
static int refresh_ids_and_size(Node *head);

int criteria(const char *type)
{
    if (type == NULL)
    {
        printf("Invalid criteria\n");
        return -1;
    }

    size_t len = strlen(type);
    char *select = malloc(len + 1);
    if (select == NULL)
    {
        printf("Error allocating memory for criteria\n");
        return -1;
    }

    memcpy(select, type, len + 1);
    to_uppercase_inplace(select);

    int selected_criteria = help_selected(select);
    free(select);

    if (selected_criteria >= 0)
        return selected_criteria;

    printf("Not option, try number of queue, name, times and type");
    return -1;
}

static int help_selected(const char *selected)
{
    if (strcmp("ID", selected) == 0)
        return 0;
    if (strcmp("NAME", selected) == 0)
        return 1;
    if (strcmp("TIME_INIT", selected) == 0)
        return 2;
    if (strcmp("TIME_END", selected) == 0)
        return 3;
    if (strcmp("DESCRIPTION", selected) == 0)
        return 4;
    if (strcmp("TYPE", selected) == 0)
        return 5;
    return -1;
}

static void to_uppercase_inplace(char *text)
{
    for (; *text != '\0'; ++text)
    {
        *text = (char)toupper((unsigned char)*text);
    }
}

static int refresh_ids_and_size(Node *head)
{
    int id = 1;
    Node *current = head;

    while (current != NULL)
    {
        if (current->data != NULL)
        {
            current->data->id = id;
        }
        current = current->next;
        id++;
    }

    int size = id - 1;
    current = head;
    while (current != NULL)
    {
        current->size = size;
        current = current->next;
    }

    return size;
}

Node *create_node(Work *data)
{
    const int number_node = 1;

    if (data == NULL)
    {
        printf("Cannot create a node with null data");
        return NULL;
    }

    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        printf("Error trying to create a node");
        return NULL;
    }

    new_node->data = data;
    new_node->next = NULL;
    new_node->data->id = number_node;
    new_node->size = number_node;

    return new_node;
}

// Insert a new node after head
void insert_node(Node *head, Work *data)
{
    if (head == NULL || data == NULL)
    {
        printf("Cannot adding a new node without create a new one");
        return;
    }

    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        printf("Error trying to insert new node");
        return;
    }

    new_node->data = data;
    new_node->next = head->next;
    new_node->size = 0;
    head->next = new_node;

    head->size = refresh_ids_and_size(head);
    new_node->size = head->size;
}

// Insert a new node in final
void append_node(Node *head, Work *data)
{
    if (head == NULL || head->data == NULL || data == NULL)
    {
        printf("Cannot adding a new node without create a new one");
        return;
    }

    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        printf("Error trying to insert new node");
        return;
    }

    new_node->data = data;
    new_node->next = NULL;
    new_node->size = 0;

    Node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_node;
    head->size = refresh_ids_and_size(head);
    new_node->size = head->size;
}

void ording_node(Node *head, int criteria)
{
    if (head == NULL || criteria < 0 || criteria > 5)
    {
        printf("There aren't work for ording");
        return;
    }

    if (head->size > 1)
    {
        merge_sort(head, 0, head->size - 1, criteria);
    }
    head->size = refresh_ids_and_size(head);
}

void remove_node(Node *head, int id)
{
    if (head == NULL || head->data == NULL)
    {
        printf("There aren't node, try create and remove after");
        return;
    }

    if (id <= 0)
    {
        printf("Invalid id");
        return;
    }

    if (head->data->id == id)
    {
        if (head->next == NULL)
        {
            printf("Cannot remove the only node in list");
            return;
        }

        head->data = head->next->data;
        head->next = head->next->next;
        free_node(head->next);
        free_work(head->data);
        head->size = refresh_ids_and_size(head);
        return;
    }

    Node *prev = head;
    Node *current = head->next;

    while (current != NULL)
    {
        if (current->data != NULL && current->data->id == id)
        {
            prev->next = current->next;
            free_node(current);
            free_work(current->data);
            head->size = refresh_ids_and_size(head);
            return;
        }
        prev = current;
        current = current->next;
    }
}

Work *create_work(const char *name, const char *description,
                  const Time *time_end, Type type)
{
    Work *work = malloc(sizeof(Work));

    if (work == NULL)
    {
        printf("Error try create a new Work");
        return NULL;
    }

    work->id = 0;
    work->name = name;
    work->description = description;
    work->time_init = new_current_time();
    work->time_end = time_end;
    work->type = type;

    return work;
}
