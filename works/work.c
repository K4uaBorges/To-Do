#include "work.h"

static int help_selected(const char *selected);
static void to_uppercase_inplace(char *text);

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

Node *create_node(Work *data)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        printf("Error trying to create a node");
        return NULL;
    }

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

// Insert a new node after head
void insert_node(Node *head, Work *data)
{
    if (head == NULL || head->data == NULL)
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
    head->next = new_node;
}

// Insert a new node in final
void append_node(Node *head, Work *data)
{
    if (head == NULL || head->data == NULL)
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

    Node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_node;
};

void *ordered_Work(Work *data, Node *head,
                   bool (*compare)(const Work *, const Work *, int), int criteria)
{
}

Work *create_work(int id, const char *name, const char *description,
                  const Time *time_end, Type type)
{
    Work *work = malloc(sizeof(Work));

    if (work == NULL)
    {
        printf("Error try create a new Work");
        return NULL;
    }

    work->id = id;
    work->name = name;
    work->description = description;
    work->time_init = new_current_time();
    work->time_end = time_end;
    work->type = type;

    return work;
}
