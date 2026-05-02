#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <sys/resource.h>

void floyd(int a[][20], int n)
{
	int k, i, j;

	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (a[i][j] > (a[i][k] + a[k][j]))
					a[i][j] = a[i][k] + a[k][j];

	printf("All Pairs Shortest Paths:\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf("%d\t", a[i][j]);
		printf("\n");
	}
}

void main()
{
	struct timeval tv1, tv2;
	struct rusage r_usage;
	int n, a[20][20], i, j;

	printf("Enter the number of vertices\n");
	scanf("%d", &n);

	printf("Enter the cost adjacency matrix for the graph [999 for no edge, 0 for self loops]:\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &a[i][j]);

	gettimeofday(&tv1, NULL);
	floyd(a, n);
	gettimeofday(&tv2, NULL);

	printf("Time of Floyd's Algorithm = %f microseconds\n",(double)(tv2.tv_usec - tv1.tv_usec));
	getrusage(RUSAGE_SELF, &r_usage);
	printf("Memory usage = %ld kilobytes\n", r_usage.ru_maxrss);
}

//Output:
/*Enter the number of vertices: 3
Enter the cost adjacency matrix for the graph [999 for no edge, 0 for self loops]:
0 2 999
999 0 3
4 999 0
All Pairs Shortest Paths:
0       2       5
7       0       3
4       6       0
Time of Floyd's Algorithm = 25.000000 microseconds
Memory usage = 3072 kilobytes*/