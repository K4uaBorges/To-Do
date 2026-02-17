#include "work.h"

Node *create_node(Work *data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));

    if (new_node == NULL)
    {
        fprint(stderr, "Error trying to create a node");
        return NULL;
    };

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
};

// Insert a new node after head
void insert_node(Node *head, Work *data)
{

    if (head->data == NULL)
    {
        fprint(stderr, "Cannot adding a new node without create a new one");
        return;
    };

    Node *new_node = (Node *)malloc(sizeof(Node));

    if (new_node == NULL)
    {
        fprint(stderr, "Error trying to insert new node");
        return;
    };

    new_node->data = data;
    new_node->next = head->next;
    head->next = new_node;
};

// Insert a new node in final
void append_node(Node *head, Work *data)
{
    if (head->data == NULL)
    {
        fprint(stderr, "Cannot adding a new node without create a new one");
        return;
    };

    Node *new_node = (Node *)malloc(sizeof(Node));

    if (new_node == NULL)
    {
        fprint(stderr, "Error trying to insert new node");
        return;
    };

    new_node->data = data;
    new_node->next = NULL;
    head->next = new_node;
};

Work *create_work(int id, const char *name, const char *description,
                  const Time *time_end, Type type)
{

    Work *work = (Work *)malloc(sizeof(Work));

    if (work == NULL)
    {
        fprintf(stderr, "Error try create a new Work");
    };

    work->id = id;
    work->name = name;
    work->description = description;
    work->time_init = new_current_time();
    work->time_end = time_end;
    work->type = type;

    create_node(work);

    return work;
};
