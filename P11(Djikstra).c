#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

void dijkstra(int n, int a[10][10], int v)
{
	int i, j, s[10], d[10], k, min, u;

	for (i = 1; i <= n; i++) {
		s[i] = 0;
		d[i] = a[v][i];
	}

	d[v] = 0;
	s[v] = 1;

	for (k = 2; k <= n; k++) {
		min = 999;

		for (i = 1; i <= n; i++) {
			if (s[i] == 0 && d[i] < min) {
				min = d[i];
				u = i;
			}
		}

		s[u] = 1;

		for (i = 1; i <= n; i++) {
			if (s[i] == 0) {
				if (d[i] > (d[u] + a[u][i])) {
					d[i] = d[u] + a[u][i];
				}
			}
		}
	}

	printf("The shortest distance from %d is:\n", v);
	for (i = 1; i <= n; i++) {
		printf("%d --> %d = %d\n", v, i, d[i]);
	}
}

int main()
{
	int n, i, j, a[10][10], v;
	struct timeval tv1, tv2;
	struct rusage r_usage;

	printf("Enter the number of vertices:\n");
	scanf("%d", &n);

	printf("Enter the cost matrix (Enter 999 if no edge):\n");
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			scanf("%d", &a[i][j]);

	printf("Enter the source vertex:\n");
	scanf("%d", &v);

	gettimeofday(&tv1, NULL);
	dijkstra(n, a, v);
	gettimeofday(&tv2, NULL);

	printf("Time of Dijkstra's Algorithm = %f microseconds\n",(double)(tv2.tv_usec - tv1.tv_usec));

	getrusage(RUSAGE_SELF, &r_usage);
	printf("Memory usage: %ld kilobytes\n", r_usage.ru_maxrss);

	return 0;
}

//Output:
/*
Enter the number of vertices:	4

Enter the cost matrix (Enter 999 if no edge):
0 2 5 999
4 0 3 5
999 2 0 4
1 3 2 0

Enter the source vertex: 1

The shortest distance from 1 is:
1 --> 1 = 0
1 --> 2 = 2
1 --> 3 = 5
1 --> 4 = 7
Time of Dijkstra's Algorithm = 27.000000 microseconds
Memory usage: 3328 kilobytes*/