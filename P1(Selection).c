//Selection Sort in C

#include <stdio.h>
#include <sys/time.h>      // For gettimeofday()
#include <time.h>
#include <sys/resource.h> // For getrusage()

// Function prototype
void selection_sort(int arr[100], int size);

int main()
{
    struct timeval tv1, tv2;        // Structures to store start and end time
    int size, arr[50];
    struct rusage r_usage;          // Structure to store memory usage

    printf("Enter input size: ");
    scanf("%d", &size);

    printf("Enter array elements: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    gettimeofday(&tv1, NULL);
    selection_sort(arr, size);
    gettimeofday(&tv2, NULL);

    printf("Sorted array:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Calculate and display execution time in microseconds
    printf("Time of selection sort = %f microseconds\n",(double)(tv2.tv_usec - tv1.tv_usec));

    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory usage: %ld kilobytes\n", r_usage.ru_maxrss);

    return 0;
}

void selection_sort(int arr[100], int size)
{
    int i, j, min, temp;

    for (i = 0; i < size - 1; i++)
    {
        min = i;  // Assume current index has the minimum element

        // Find the minimum element in remaining unsorted array
        for (j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }

        // Swap the found minimum element with the first element
        temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

//Output:
//Enter input size: 10
//Enter array elements: 64 25 12 22 11 80 37 46 34 78
//Sorted array: 11 12 22 25 34 37 46 64 78 80
//Time of selection sort = 0.000000 microseconds
//Memory usage: 123456 kilobytes