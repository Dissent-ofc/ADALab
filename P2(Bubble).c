#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/resource.h>


void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(int arr[], int size)
{
    bool swapped;
    for (int i = 0; i < size - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < size - i - 1; j++)
        {
            // If current element is greater than next element swap them
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped, array is already sorted
        if (swapped == false)
            break;
    }
}

int main()
{
    int size, arr[100];
    struct timeval tv1, tv2;
    struct rusage r_usage;

    printf("Enter array size: ");
    scanf("%d", &size);

    printf("Enter array elements: ");
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    gettimeofday(&tv1, NULL);
    bubbleSort(arr, size);
    gettimeofday(&tv2, NULL);

    printf("Sorted array: \n");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Time of bubble sort = %f microseconds\n",(double)(tv2.tv_usec - tv1.tv_usec));

    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory usage: %ld kilobytes\n", r_usage.ru_maxrss);

    return 0;
}

//Output:
//Enter array size: 10
//Enter array elements: 4 7 34 67 44 12 9 13 45 65
//Sorted array: 4 7 9 12 13 34 44 45 65 67
//Time of bubble sort = 0.000000 microseconds
//Memory usage: 123456 kilobytes