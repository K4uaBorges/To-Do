#include "todo_time.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void free_time(Time *time)
{
    if (time != NULL)
    {
        free(time);
    }
    else
    {
        fprintf(stderr, "There aren't time");
    }
};

Time *malloc_time(void)
{
    Time *time = (Time *)malloc(sizeof(Time));
    if (time == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for Time\n");
        return NULL;
    }
    return time;
};

Time *create_time(void)
{
    Time *time = malloc_time();
    if (time == NULL)
        return NULL;

    return time;
};

void update_time(Time *dst, unsigned int year, unsigned int month, unsigned int day,
                 unsigned int hour, unsigned int minute, unsigned int second)
{
    if (time == NULL)
    {
        fprintf(stderr, "Failed in update, this date not exist, try create");
        return;
    }

    dst->year = year;
    dst->month = month;
    dst->day = day;
    dst->hour = hour;
    dst->minute = minute;
    dst->second = second;
};

void remove_time(Time *dst)
{
    free_time(dst);
};

void current_time(Time *dst)
{
    if (dst == NULL)
    {
        fprintf(stderr, "Destination Time is NULL\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *actual_time = localtime(&now);

    if (actual_time != NULL)
    {
        dst->year = (unsigned int)(actual_time->tm_year + 1900); // tm_year = Year - 1900
        dst->month = (unsigned int)(actual_time->tm_mon + 1);    // tm_mon is 0-11
        dst->day = (unsigned int)actual_time->tm_mday;
        dst->hour = (unsigned int)actual_time->tm_hour;
        dst->minute = (unsigned int)actual_time->tm_min;
        dst->second = (unsigned int)actual_time->tm_sec;
    }
}

Time *new_current_time()
{
    Time *dst = create_time();
    current_time(dst);
    return dst;
}
