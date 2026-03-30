#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <sys/resource.h>

void merge(int arr[], int left, int mid, int right)
{
	int i, j, k;

	int n1 = mid - left + 1;
	int n2 = right - mid;
	int L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[left + i];

	for (j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	i = 0;
	j = 0;
	k = left;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j])
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}

	while (i < n1)
		arr[k++] = L[i++];

	while (j < n2)
		arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right)
{
	if (left < right)
    {
		int mid = left + (right - left) / 2;

		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

int main()
{
	struct timeval tv1, tv2;
	struct rusage r_usage;
	int size, i, arr[100];

	printf("Enter number of elements: ");
	scanf("%d", &size);

	printf("Enter %d elements:\n", size);
	for (i = 0; i < size; i++)
		scanf("%d", &arr[i]);

	gettimeofday(&tv1, NULL);
	mergeSort(arr, 0, size - 1);
	gettimeofday(&tv2, NULL);

	printf("Sorted array:\n");
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);

	printf("\ntime of merge sort = %f microseconds\n",(double)(tv2.tv_usec - tv1.tv_usec));

	getrusage(RUSAGE_SELF, &r_usage);
	printf("memory usage: %ld kilobytes\n", r_usage.ru_maxrss);

	return 0;
}

//Output:
//Enter number of elements: 10
//Enter 10 elements: 38 27 43 3 9 82 10 5 1 7
//Sorted array: 1 3 5 7 9 10 27 38 43 82
//time of merge sort = 0.000000 microseconds