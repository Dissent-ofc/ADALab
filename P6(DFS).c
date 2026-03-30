#include <stdio.h>
#include <sys/time.h>     // For gettimeofday
#include <sys/resource.h> // For getrusage

int a[20][20], reach[20], size;

void dfs(int v)
{
    int i;
    reach[v] = 1;
    for (i = 1; i <= size; i++) {
        if (a[v][i] && !reach[i]) {
            printf("\n %d->%d", v, i);
            dfs(i);
        }
    }
}

void main() 
{
    int i, j, v, count = 0;
    struct timeval tv1,tv2;      // Structures to store time
    struct rusage r_usage;       // Variable for memory usage info

    printf("\n Enter number of vertices:");
    scanf("%d", &size);

    for (i = 1; i <= size; i++) {
        reach[i] = 0;
        for (j = 1; j <= size; j++)
            a[i][j] = 0;
    }

    printf("\n Enter the adjacency matrix:\n");
    for (i = 1; i <= size; i++)
        for (j = 1; j <= size; j++)
            scanf("%d", &a[i][j]);

    printf("Enter the source vertex:\n");
    scanf("%d", &v);


    gettimeofday(&tv1, NULL);
    dfs(v);
    gettimeofday(&tv2, NULL);

    printf("\n");
    for (i = 1; i <= size; i++) {
        if (reach[i])
            count++;
    }

    printf("Time of DFS=%f microseconds",(double)(tv2.tv_usec-tv1.tv_usec));
    getrusage(RUSAGE_SELF,&r_usage);
    printf("Memory usage:%ld kilobytes",r_usage.ru_maxrss);  

    /* Check for connectivity */
    if(count == size)
        printf("\nGraph is connected\n");
    else
        printf("\nGraph is not connected\n");
}

//Output:
//Enter number of vertices:5
//Enter the adjacency matrix:
//0 1 1 0 0
//1 0 1 1 0
//1 1 0 0 1
//0 1 0 0 1
//0 0 1 1 0
//Enter the source vertex:1
// 1->2
// 2->3
// 2->4
// 3->5
//Time of DFS=123.000000 microseconds
//Memory usage:12345 kilobytes
//Graph is connected