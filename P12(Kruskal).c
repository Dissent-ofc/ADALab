#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int min, cost[100][100], parent[100], i, j, x, y, n;

void find_min(void);
int check_cycle(int x, int y);

int main()
{
	struct timeval tv1, tv2;
	struct rusage r_usage;
	int count = 0, tot = 0, flag = 0;

	printf("Enter the number of vertices \n");
	scanf("%d", &n);

	printf("Enter the cost matrix \n");
	printf("Enter 999 for No edges and self loops \n");
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			scanf("%d", &cost[i][j]);
			parent[j] = 0;
		}
	}

	gettimeofday(&tv1, NULL);
	while (count != n - 1 && min != 999) {
		find_min();

		flag = check_cycle(x, y);
		if (flag == 1) {
			printf("\n%d -----> %d == %d\n", x, y, cost[x][y]);
			count++;
			tot += cost[x][y];
		}

		cost[x][y] = cost[y][x] = 999;
	}
	gettimeofday(&tv2, NULL);

	printf("\nThe total cost of minimum spanning tree = %d\n", tot);

	printf("Time of Kruskal's Algorithm = %f microseconds\n",(double)(tv2.tv_usec - tv1.tv_usec));

	getrusage(RUSAGE_SELF, &r_usage);
	printf("Memory usage: %ld kilobytes\n", r_usage.ru_maxrss);

	return 0;
}

void find_min(void)
{
	min = 999;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			if (cost[i][j] < min) {
				min = cost[i][j];
				x = i;
				y = j;
			}
		}
	}
}

int check_cycle(int x, int y)
{
	if ((parent[x] == parent[y]) && (parent[x] != 0))
		return 0;
	else if (parent[x] == 0 && parent[y] == 0)
		parent[x] = parent[y] = x;
	else if (parent[x] == 0)
		parent[x] = parent[y];
	else if (parent[x] != parent[y])
		parent[y] = parent[x];
	return 1;
}

//Output:
/*
Enter the number of vertices:5
Enter the cost matrix 
Enter 999 for No edges and self loops 
999 4 999 6 999
4 999 3 2 999
999 3 999 999 1    
6 2 999 999 2
999 999 1 2 999

3 -----> 5 == 1
2 -----> 4 == 2
4 -----> 5 == 2
2 -----> 3 == 3

The total cost of minimum spanning tree = 8
Time of Kruskal's Algorithm = 30.000000 microseconds
Memory usage: 3200 kilobytes*/