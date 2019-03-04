#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int is_prime(int x)
{
	for (int i = 2; i <= floor(sqrt(x)); i++)
	{
		if (x % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

int odd_is_prime(int x)
{
	if (x == 2) return 1;
	for (int i = 3; i <= floor(sqrt(x)); i += 2)
	{
		if (x % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

int *prime(int(*check)(int), int a, int b)
{
	int *primes = (int*)calloc(b - a + 1, sizeof(int));
	int j = 0;
	for (int i = a; i <= b; i++)
	{
		if (check(i) == 1)
		{
			primes[j] = i;
			j++;
		}
	}
	return primes;
}

int *odd_prime(int(*check)(int), int a, int b)
{
	int *primes = (int*)calloc(b - a + 1, sizeof(int));
	int j = 0;
	if (a <= 2)
	{
		primes[j] = 2;
		return primes;
	}
	if (a % 2 == 0) a++;
	for (int i = a; i <= b; i += 2)
	{
		if (check(i) == 1)
		{
			primes[j] = i;
			j++;
		}
	}
	return primes;
}

void print_primes(int* primes, int size)
{
	int i = 0;
	while (primes[i] != 0 && i < size)
	{
		printf("%d ", primes[i]);
		i++;
	}
	printf("\n");
}

int main()
{
	clock_t start_prime, end_prime;
	clock_t start_odd_prime, end_odd_prime;
	clock_t start_odd_odd_prime, end_odd_odd_prime;
	double time_prime, time_odd_prime, time_odd_odd_prime;
	int a, b;
	printf("a = ");
	scanf_s("%d", &a);
	printf("\nb = ");
	scanf_s("%d", &b);
	if (a < 0 || b < 0)
	{
		printf("Numbers can't be negative!\n");
		return 0;
	}
	if (a > b)
	{
		int c = a;
		a = b;
		b = c;
	}
	/*start_prime = clock();
	int *primes = prime(is_prime, a, b);
	end_prime = clock();
	time_prime = ((double)(end_prime - start_prime)) / CLOCKS_PER_SEC;*/

	start_odd_prime = clock();
	int *odd_primes = odd_prime(is_prime, a, b);
	end_odd_prime = clock();
	time_odd_prime = ((double)(end_odd_prime - start_odd_prime)) / CLOCKS_PER_SEC;

	start_odd_odd_prime = clock();
	int *odd_odd_primes = odd_prime(odd_is_prime, a, b);
	end_odd_odd_prime = clock();
	time_odd_odd_prime = ((double)(end_odd_odd_prime - start_odd_odd_prime)) / CLOCKS_PER_SEC;

	//print_primes(primes, b - a + 1);
	//printf("Prime time: %lf\n", time_prime);
	//print_primes(odd_primes, b - a + 1);
	printf("Prime + odd time: %lf\n", time_odd_prime);
	//print_primes(odd_odd_primes, b - a + 1);
	printf("Prime + odd + odd time: %lf\n", time_odd_odd_prime);
	getchar();
	getchar();
	return 0;
}