#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

/* for simplicity the # of procs is defined here,
But a better idea is to read it from the command line */
#define PROCESSES 	8
#define BILLION  	1000000000L
#define START 		2
#define END 		200000

int is_perfect(int x)
{
	int sum = 0;
	for (int i = 1; i <= x / 2; i++)
	{
		if (x % i == 0)
		{
			sum += i;
		}
	}
	if (x == sum) return 1;
	return 0;
}

void checkInterval(int start, int end)
{
	if (start < 2) 
	{
		start = 2;
	}
	for (int i = start; i <= end; i++)
	{
		if (is_perfect(i))
		{
			printf("i = %d\n", i);
		}
	}
}

void checkIntervalLB(int start, int end)
{
	for (int i = start; i <= end; i+= PROCESSES)
	{
		if (is_perfect(i))
		{
			printf("%d\n", i);
		}
	}
}

void do_work(int i) 
{
	printf("Hello there, from process %d! \n", i);
}

int main()
{
	struct timespec start, stop;
	int i, pid, size = END / PROCESSES;
	double accum;
	/* Take initial time here */
	/* Use clock_gettime(). Do NOT use clock() */
	
	if(clock_gettime(CLOCK_REALTIME, &start) == -1) {
      perror("clock gettime");
      exit(EXIT_FAILURE);
    }
	
	for(i = 0; i < PROCESSES; i++)
	{
		pid = fork();
		if(pid < 0) /* some error occurred – fork failed */
		{
			printf("Error\n");
			exit(-1);
		}
		if(pid == 0) /* child process code */
		{
			checkIntervalLB(START + i, END);
			exit(0);
		}
		/* do not place any wait() call here */
	}
	/* wait for all processes to finish their execution */
	for(i = 0; i < PROCESSES; i++)
		wait(NULL);
	/* Take final time here */
	/* Use clock_gettime(). Do NOT use clock() */
	/* Compute the execution time*/
	if (clock_gettime( CLOCK_REALTIME, &stop) == -1) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
	accum = (stop.tv_sec - start.tv_sec)
          + (stop.tv_nsec - start.tv_nsec)
            / (double) BILLION;
    printf("%lf s\n", accum);
	return(EXIT_SUCCESS);
}