#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <sys/resource.h>

char str[100], ptn[20];
int res, m, n, i, j, k, table[1000];

void shift(char ptn[]);
int horspool(char ptn[], char text[]);

void main()
{
	struct timeval tv1, tv2;
	struct rusage r_usage;

	printf("Enter the text:\n");
	gets(str);

	printf("Enter the pattern to be found:\n");
	gets(ptn);

	gettimeofday(&tv1, NULL);
    res = horspool(ptn, str);
    gettimeofday(&tv2, NULL);

	if (res == -1)
		printf("\nPattern not found\n");
	else
		printf("\nPattern found at %d position\n", res + 1);

	printf("Time of Horsepool= %f microseconds\n",(double)(tv2.tv_usec - tv1.tv_usec));
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory usage = %ld kilobytes\n", r_usage.ru_maxrss);
}

void shift(char ptn[])
{
	int len = strlen(ptn);
    for (i = 0; i < 1000; i++)
		table[i] = len;

	for (j = 0; j <= len - 2; j++)
		table[ptn[j]] = len - 1 - j;
}

int horspool(char ptn[], char str[])
{
	shift(ptn);

	m = strlen(ptn);
	n = strlen(str);
	i = m - 1;

	while (i <= n - 1) {
		k = 0;

		while ((k <= m - 1) && (ptn[m - 1 - k] == str[i - k]))
			k++;

		if (k == m)
			return (i - m + 1);
		else
			i = i + table[str[i]];
	}
    return -1;
}

//Output:
//Enter the text:hello world
//Enter the pattern to be found:world
//Pattern found at 7 position
//Time of Horsepool= 0.000000 microseconds
//Memory usage = 0 kilobytes