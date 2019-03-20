#include <stdio.h>
#include <unistd.h>
#include <time.h>
/* for simplicity the # of procs is defined here,
But a better idea is to read it from the command line */
#define PROCESSES 4
main()
{
int i, pid;
/* Take initial time here */
/* Use clock_gettime(). Do NOT use clock() */
for(i=0; i<PROCESSES; i++)
{
pid = fork();
if(pid < 0) /* some error occurred – fork failed */
{
printf(“Error”);
exit(-1);
}
if(pid == 0) /* child process code */
{
do_work(i);
exit(0);
}
/* do not place any wait() call here */
}
/* wait for all processes to finish their execution */
for(i=0; i<PROCESSES; i++)
wait(NULL);
/* Take final time here */
/* Use clock_gettime(). Do NOT use clock() */
/* Compute the execution time*/
}
/* this function is executed by each process */
do_work(int i)
{
printf(“Hello there, from process %d! \n”, i);
/* rest of the code goes here */
}