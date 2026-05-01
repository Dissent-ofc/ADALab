#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

void warshall(int a[][20], int n)
{
    int k, i, j;

    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                a[i][j] = (a[i][j] || a[i][k] && a[k][j]);
}

void main()
{
    int n, a[20][20], i, j;
    struct timeval tv1, tv2;
    struct rusage r_usage;

    printf("\nenter number of nodes in the graph\n");
    scanf("%d", &n);

    printf("Enter the adjacency matrix for the graph:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &a[i][j]);

    gettimeofday(&tv1, NULL);
    warshall(a, n);
    gettimeofday(&tv2, NULL);

    printf("the path matrix is\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d\t", a[i][j]);
        printf("\n");
    }

    printf("Time of Warshall = %f microseconds\n",(double)(tv2.tv_usec - tv1.tv_usec));
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory usage: %ld kilobytes\n", r_usage.ru_maxrss);
}

//Output:
//enter number of nodes in the graph:   4
//Enter the adjacency matrix for the graph:
//0 1 0 0
//0 0 1 0
//0 0 0 1
//1 0 0 0

//the path matrix is
//1       1       1       1
//1       1       1       1
//1       1       1       1
//1       1       1       1

//Time of Warshall = 1.000000 microseconds
//Memory usage: 3328 kilobytes