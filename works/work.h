#ifndef WORK_H
#define WORK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../api/todo_time.h"

typedef enum
{
    IMPORTANT,
    NORMAL,
    LOW
} Type;

typedef struct works
{
    int id;
    char *name;
    char *description;
    Time *time_init;
    Time *time_end;
    Type type;
} Work;

typedef struct work_node
{
    Work *data;
    struct Node *next;
} Node;

// criteria: 0 for id, 1 for name, 2 for time_init, 4 for time_end, 5 for type
int criteria(char *ording);

// Function to create a new work
Work *create_work(int id, const char *name, const char *description, const Time *time_end, Type type);

// Update a work's information
void update_work(Work *work, const char *name, const char *description, const Time *time_init, const Time *time_end, Type type);

// Function to remove a work from the list
Work *remove_work(Work *work);

// Function to get a work
Work *get_work(int criteria);
Work *get_all_works();

// Function to print a work or Node information
void print_work(Work *work);
void print_node

    // Function to compare two works, if work1 is greater or equal to than work2, return true, otherwise return false
    bool compare_works(const Work *work1, const Work *work2, int criteria);

// Nodes helping for search, sort, and become a system more fast and efective
Node *create_node(Work *work);
void insert_node(Node *head, Work *data);
void append_node(Node *head, Work *data);
void *ordered_Work(Work *data, Node *head, bool (*compare)(const Work *, const Work *, int), int criteria);
void remove_node(Node *head, int id);
Node *nodeAll(Node *head);

// function to free or allocate memory for work
void free_work(Work *work);
void free_node(Node *node);
void free_all_nodes(Node *head);
void malloc_work(Work *work);
void malloc_node(Node *node);

// Functions to search and sort works
Node *search_work(Node *head, int criteria, Work *value);
void change_node(Node *head, int id, Work *new_work);
void merge_sort(int *arr, int left, int right, int criteria);

// Fuction to Write and Read the works in a file
void write_works_to_file(const char *filename, Node *head);
Node *read_works_from_file(const char *filename);

#endif
