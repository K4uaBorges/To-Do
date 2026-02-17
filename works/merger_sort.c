#include "work.h"

static int compare_int(int a, int b);
static int compare_id(int a, int b);
static int compare_string(const char *a, const char *b);
static int compare_time(const Time *a, const Time *b);
static int compare_work_values(const Work *work1, const Work *work2, int criteria);
static void merge(Work **arr, int left, int mid, int right, int criteria);

static int compare_int(int a, int b)
{
    return (a > b) - (a < b);
};

static int compare_id(int a, int b)
{
    return compare_int(a, b);
};

static int compare_string(const char *a, const char *b)
{
    if (a == b)
    {
        return 0;
    }
    if (a == NULL)
    {
        return 1;
    }
    if (b == NULL)
    {
        return -1;
    }
    return strcmp(a, b);
};

static int compare_time(const Time *a, const Time *b)
{
    if (a == b)
    {
        return 0;
    }
    if (a == NULL)
    {
        return 1;
    }
    if (b == NULL)
    {
        return -1;
    }

    int result = compare_int((int)a->year, (int)b->year);
    if (result != 0)
    {
        return result;
    }

    result = compare_int((int)a->month, (int)b->month);
    if (result != 0)
    {
        return result;
    }

    result = compare_int((int)a->day, (int)b->day);
    if (result != 0)
    {
        return result;
    }

    result = compare_int((int)a->hour, (int)b->hour);
    if (result != 0)
    {
        return result;
    }

    result = compare_int((unsigned int)a->minute, (unsigned int)b->minute);
    if (result != 0)
    {
        return result;
    }

    return compare_int((unsigned int)a->second, (unsigned int)b->second);
};

static int compare_work_values(const Work *work1, const Work *work2, int criteria)
{
    if (work1 == work2)
    {
        return 0;
    };
    if (work1 == NULL)
    {
        return -1;
    };
    if (work2 == NULL)
    {
        return -1;
    };

    switch (criteria)
    {
    case 0:
        return compare_id(work1->id, work2->id);
    case 1:
        return compare_string(work1->name, work2->name);
    case 2:
        return compare_time(work1->time_init, work2->time_init);
    case 3:
        return compare_time(work1->time_end, work2->time_end);
    case 4:
        return compare_string(work1->description, work2->description);
    case 5:
        return compare_int((int)work1->type, (int)work2->type);
    default:
        return 0;
    };
};

bool compare_works(const Work *work1, const Work *work2, int criteria)
{
    return compare_work_values(work1, work2, criteria) >= 0;
};

static void merge(Work **arr, int left, int mid, int right, int criteria)
{
    int i = 0;
    int j = 0;
    int k = left;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Work **left_arr = malloc((size_t)n1 * sizeof(Work *));
    Work **right_arr = malloc((size_t)n2 * sizeof(Work *));

    if (left_arr == NULL || right_arr == NULL)
    {
        free(left_arr);
        free(right_arr);
        printf("Error allocating memory in merge_sort\n");
        return;
    };

    for (i = 0; i < n1; i++)
    {
        left_arr[i] = arr[left + i];
    };
    for (j = 0; j < n2; j++)
    {
        right_arr[j] = arr[mid + 1 + j];
    };

    i = 0;
    j = 0;
    while (i < n1 && j < n2)
    {
        if (compare_work_values(left_arr[i], right_arr[j], criteria) <= 0)
        {
            arr[k] = left_arr[i];
            i++;
        }
        else
        {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    };

    while (i < n1)
    {
        arr[k] = left_arr[i];
        i++;
        k++;
    };

    while (j < n2)
    {
        arr[k] = right_arr[j];
        j++;
        k++;
    };

    free(left_arr);
    free(right_arr);
};

void merge_sort(Work **arr, int left, int right, int criteria)
{
    if (arr == NULL || left < 0 || right < 0 || left >= right)
    {
        return;
    };

    if (criteria < 0 || criteria > 5)
    {
        printf("Invalid criteria for merge_sort\n");
        return;
    };

    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid, criteria);
    merge_sort(arr, mid + 1, right, criteria);
    merge(arr, left, mid, right, criteria);
    ;
}
