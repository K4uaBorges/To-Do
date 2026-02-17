#ifndef TODO_API_TIME_H
#define TODO_API_TIME_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

// Struct of time
typedef struct time
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
} Time;

// Struct time of library C
typedef struct tm TM;

// Function allocate or free memory for Time
void free_time(Time *time);
Time *malloc_time(void);

// Function to create a new time
Time *create_time(unsigned int year, unsigned int month, unsigned int day,
                  unsigned int hour, unsigned int minute, unsigned int second);

// Function to update a time's information
void update_time(Time *time, unsigned int year, unsigned int month, unsigned int day,
                 unsigned int hour, unsigned int minute, unsigned int second);

// Function to remove a time
void remove_time(Time *time);

// Function to get the current time
void current_time(Time *time);

// Function important to get in real time for work.c
Time *new_current_time();

#endif
