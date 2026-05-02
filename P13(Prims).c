#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <sys/resource.h>

int n, c[20][20], i, j, visited[20];

void prim()
{
    int min, a, b, cost=0, count=0;
    visited[1] = 1;

    while(count < n - 1)
    {
        min = 999;
        a = -1;
        b = -1;

        for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= n; j++)
            {
                if(visited[i] && !visited[j] && c[i][j] < min)
                {
                    min = c[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        if(a != -1 && b != -1)
        {
            printf("%d ---> %d = %d\n", a, b, c[a][b]);
            cost += c[a][b];
            visited[b] = 1;
            count++;
        }
    }
    printf("Total cost of Spanning tree is %d\n", cost);
}

int main()
{
    struct timeval tv1, tv2;
    struct rusage r_usage;

    printf("Enter number of vertices \n");
    scanf("%d", &n);

    printf("Enter the cost matrix \n");
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
            scanf("%d", &c[i][j]);
        visited[i] = 0;
    }

    gettimeofday(&tv1, NULL);
    prim();
    gettimeofday(&tv2, NULL);

	printf("Time of Prim's Algorithm = %f microseconds\n",(double)(tv2.tv_usec - tv1.tv_usec));

    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory usage: %ld kilobytes\n", r_usage.ru_maxrss);

    return 0;
}

//Output:
/*
Enter number of vertices: 4

Enter the cost matrix: 
999 10 6 5
10 999 999 15
6 999 999 4
5 15 4 999

1 ---> 4 = 5
4 ---> 3 = 4
1 ---> 2 = 10

Total cost of Spanning tree is: 19

Time of Prim's Algorithm = 116.000000 microseconds
Memory usage: 3328 kilobytes
*/