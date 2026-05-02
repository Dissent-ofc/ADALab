#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>

int count = 0, x[100];

int place(int k, int i);
void nqueen(int k, int n);

int main()
{
	int n;
	struct timeval tv1, tv2;
	struct rusage r_usage;

	printf("\t\t\tN QUEEN'S PROBLEM\n");
	printf("\nEnter the number of queens: ");
	scanf("%d", &n);

	gettimeofday(&tv1, NULL);
	nqueen(1, n);
	gettimeofday(&tv2, NULL);

	if (count == 0)
		printf("\nThere is no solution for '%d - Queens' problem\n", n);
	else
		printf("\nTotal number of solutions: %d\n", count);

	printf("Time of N-Queens Algorithm = %f microseconds\n",(double)(tv2.tv_usec - tv1.tv_usec));

	getrusage(RUSAGE_SELF, &r_usage);
	printf("Memory usage: %ld kilobytes\n", r_usage.ru_maxrss);

	return 0;
}

int place(int k, int i)
{
	int j;
	for (j = 1; j < k; j++)
		if ((x[j] == i) || (abs(x[j] - i) == abs(j - k)))
			return 0;
	return 1;
}

void nqueen(int k, int n)
{
	int i, j, p;
	for (i = 1; i <= n; i++) {
		if (place(k, i)) {
			x[k] = i;
			if (k == n) {
				count++;
				printf("\nSolution %d:\n", count);
				for (j = 1; j <= n; j++) {
					for (p = 1; p <= n; p++) {
						if (x[j] == p)
							printf(" Q ");
						else
							printf(" . ");
					}
					printf("\n");
				}
			}
            else {
				nqueen(k + 1, n);
			}
		}
	}
}

//Output:
/*
N QUEEN'S PROBLEM

Enter the number of queens: 4

Solution 1:
 .  Q  .  . 
 .  .  .  Q 
 Q  .  .  . 
 .  .  Q  . 

Solution 2:
 .  .  Q  . 
 Q  .  .  . 
 .  .  .  Q 
 .  Q  .  . 
 Total number of solutions: 2
Time of N-Queens Algorithm = 174.000000 microseconds
Memory usage: 3328 kilobytes
*/