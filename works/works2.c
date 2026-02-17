#include "work.h"

void *free_work(Work *dst)
{
    if (dst == NULL)
    {
        return NULL;
    }

    if (dst->time_init != NULL)
    {
        free_time(dst->time_init);
    }

    free(dst);
}

void free_node(Node *dst)
{

    if (dst == NULL)
    {
        return NULL;
    }

    free_work(dst->data);
    free(dst);
}
