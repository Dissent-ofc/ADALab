#include<stdio.h>          // Standard input-output functions
#include<sys/time.h>       // For time measurement
#include<time.h>           // Time-related functions
#include<sys/resource.h>   // For memory usage information

// Global declarations
int arr[20][20];             // Adjacency matrix for the graph
int q[20];                 // Queue for BFS
int visited[20];           // To track visited vertices
int n,i,j;                 // Variables for vertices and loops
int f=0,r=-1;              // Front and rear of the queue

void bfs(int v) 
{
	for (i=1;i<=n;i++)
    {
        if(arr[v][i] && !visited[i])   // If edge exists and vertex not visited
        q[++r]=i;                  // Insert vertex into queue
    }
    // Process next vertex in queue
	if(f<=r) 
    {
		visited[q[f]]=1;           // Mark vertex as visited
		bfs(q[f++]);               // Recursive BFS call
	}
}

void main() {
	int v;                       // Starting vertex
    struct timeval tv1,tv2;      // Structures to store time
    struct rusage r_usage;       // Structure to store memory usage

	printf("\n Enter the number of vertices:");
	scanf("%d",&n);

    // Initialize queue and visited array
	for (i=1;i<=n;i++) 
    {
		q[i]=0;
		visited[i]=0;
	}

	printf("\nEnter graph data in matrix form:\n");
    // Read adjacency matrix
	for (i=1;i<=n;i++)
    {
        for (j=1;j<=n;j++)
        {
            scanf("%d",&arr[i][j]);
        }
    }

	printf("\nEnter the starting vertex:");
	scanf("%d",&v);

    gettimeofday(&tv1,NULL);
    bfs(v);
    gettimeofday(&tv2,NULL);

	printf("\nThe node which are reachable are:\n");
	for (i=1;i<=n;i++)
    {
        if(visited[i])
        {
            printf("%d\t",i);
        }
        else
        {
            printf("\nBfs is not possible");
        }
    }

    printf("Time of BFS=%f microseconds",(double)(tv2.tv_usec-tv1.tv_usec));
    getrusage(RUSAGE_SELF,&r_usage);
    printf("Memory usage:%ld kilobytes",r_usage.ru_maxrss);  
}

//Output:
//Enter the number of vertices:5
//Enter graph data in matrix form:
//0 1 1 0 0
//1 0 1 1 0
//1 1 0 0 1
//0 1 0 0 1
//0 0 1 1 0
//Enter the starting vertex:1
//The node which are reachable are:
//1       2       3       4       5
