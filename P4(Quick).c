#include <stdio.h>
#include <sys/time.h> // for gettimeofday()
#include <time.h>
#include <sys/resource.h> // for getrusage()

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // Pivot element
    int i = low - 1; 
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    // Place pivot at correct position
    swap(&arr[i + 1], &arr[high]);
    return i + 1; // Return partition index
}
// Recursive function to perform quick sort
void quicksort(int arr[], int low, int high)
{
    if (low < high)
    {
        // Find partition index
        int pi = partition(arr, low, high);
        // Sort elements before partition
        quicksort(arr, low, pi - 1);
        // Sort elements after partition
        quicksort(arr, pi + 1, high);
    }
}
int main()
{
    struct timeval tv1, tv2;
    struct rusage r_usage;
    int n, i, arr[50];

    printf("Enter no of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    gettimeofday(&tv1, NULL);
    quicksort(arr, 0, n - 1);
    gettimeofday(&tv2, NULL);

    printf("Sorted array:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\nTime taken by quick sort = %f microseconds",(double)(tv2.tv_usec - tv1.tv_usec));
    getrusage(RUSAGE_SELF, &r_usage);
    printf("\nMemory usage: %ld kilobytes\n",r_usage.ru_maxrss);
    return 0;
}

//Output:
//Enter no of elements: 10
//Enter the elements:56 36 78 23 11 80 37 46 34 78
//Sorted array: 11 23 34 36 37 46 56 78 78 80 
//Time taken by quick sort = 0.000000 microseconds
//Memory usage: 3328 kilobytes
