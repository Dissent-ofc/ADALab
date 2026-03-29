#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

void heapSort(int arr[], int size);
void siftDown(int arr[], int root, int bottom);

int main()
{
    int arr[100], size, i;
    struct timeval tv1, tv2;
    struct rusage r_usage;

    printf("Enter the number of elements: ");
    scanf("%d", &size);

    printf("Enter the elements:\n");
    for (i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    gettimeofday(&tv1, NULL);
    heapSort(arr, size);
    gettimeofday(&tv2, NULL);

    printf("Sorted elements are:\n");
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);

    printf("Time of HeapSort=%f microseconds", (double)(tv2.tv_usec-tv1.tv_usec));

    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory usage = %ld kilobytes\n", r_usage.ru_maxrss);

    return 0;
}

void heapSort(int arr[], int size)
{
    int i, temp;

    for (i = (size / 2) - 1; i >= 0; i--)
        siftDown(arr, i, size - 1);

    for (i = size - 1; i >= 1; i--) 
    {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        siftDown(arr, 0, i - 1);
    }
}

void siftDown(int arr[], int root, int bottom)
{
    int maxChild, temp, done = 0;

    while ((2 * root + 1) <= bottom && !done) 
    {
        if ((2 * root + 2) > bottom)
            maxChild = 2 * root + 1;
        else if (arr[2 * root + 1] > arr[2 * root + 2])
            maxChild = 2 * root + 1;
        else
            maxChild = 2 * root + 2;

        if (arr[root] < arr[maxChild]) 
        {
            temp = arr[root];
            arr[root] = arr[maxChild];
            arr[maxChild] = temp;
            root = maxChild;
        } 
        else 
        {
            done = 1;
        }
    }
}