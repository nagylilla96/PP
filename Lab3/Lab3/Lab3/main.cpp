#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int is_perfect(int x)
{
	int sum = 0;
	for (int i = 1; i < x; i++)
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
	for (int i = start; i <= end; i++)
	{
		if (is_perfect(i))
		{
			printf("%d\n", i);
		}
	}
}

void checkIntervalLB(int start, int end)
{
	for (int i = start; i <= end; i+= 4)
	{
		if (is_perfect(i))
		{
			printf("%d\n", i);
		}
	}
}

int main(int argc, char *argv[])
{
	int start, end;
	high_resolution_clock::time_point t_start, t_end;

	if (argc < 3)
	{
		printf("Usage: Lab3.exe [start] [end]\n");
		return 0;
	}

	start = atoi(argv[1]);
	end = atoi(argv[2]);

	t_start = high_resolution_clock::now();

	checkIntervalLB(start, end);

	t_end = high_resolution_clock::now();

	cout << "Time = " << duration_cast<microseconds>(t_end - t_start).count() << " ms" << endl;

	return 0;
}