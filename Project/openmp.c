#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <gmp.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <omp.h>

mpz_t a;
mpz_t b;
int threads;
unsigned long long int* primes;
int length;
mpz_t *numbers;

int isprime(int x)
{
	int i = 2;
	int square = floor(sqrt(x));
	
	while (i <= square)
	{
		if (x % i == 0)
		{
			return 0;
		}
		i++;
	}
	return 1;
}

int is_prime(const mpz_t x)
{
	mpz_t square, i;
	mpz_init_set(square, x);
	mpz_sqrt(square, x);
	mpz_init_set_si(i, 2);
	
	while (mpz_cmp(i, square) <= 0)
	{
		if (mpz_divisible_p(x, i) != 0)
		{
			mpz_clear(square);
			mpz_clear(i);
			return 0;
		}
		mpz_add_ui(i, i, 1);
	}
	mpz_clear(square);
	mpz_clear(i);
	return 1;
}

// Get the first primes 1750
unsigned long long int* getPrimes(int *n)
{
	unsigned long long int *primes = (unsigned long long int*) calloc(1750, sizeof(unsigned long long int));
	mpz_t i;
	mpz_init_set_si(i, 3);
	int size = 0;
	
	while (size < 1750)
	{
		if (is_prime(i))
		{
			primes[size] = mpz_get_ui(i);
			size++;
		}
		mpz_add_ui(i, i, 1);
	}
	*n = size;
	mpz_clear(i);
	
	return primes;
}

void print_results(unsigned long long int* nums, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%llu ", nums[i]);
	}
}

void getNumbers()
{
	numbers = malloc(sizeof(mpz_t) * length);	
	mpz_t conc;
	mpz_init_set_si(conc, 2);

	if (mpz_cmp_ui(conc, 2) > 0) 
	{
		mpz_clear(conc);
		return;
	}
	
	for (int i = 0; i < length; i++)
	{
		if (mpz_cmp(conc, b) > 0)
		{
			mpz_clear(conc);
			return;
		}
		
		mpz_init_set(numbers[i], conc);
		char *mystr = (char*) malloc(10000);
		char *temp = (char*) malloc(10000);
		mpz_get_str(mystr, 10, conc);
		snprintf(temp, 10000, "%s%llu", mystr, primes[i]);
		strcpy(mystr, temp);
		mpz_set_str(conc, mystr, 10);		
		free(mystr);
		free(temp);
	}
	mpz_clear(conc);
}

void smarandache()
{	
	#pragma omp parallel for
	for (int i = 0; i < length; i ++)
	{
		int probprime = mpz_probab_prime_p(numbers[i], 15);
		if ((probprime == 1 || probprime == 2) && (mpz_cmp(numbers[i], a) >= 0))
		{
			gmp_printf("%Zd \n", numbers[i]);
		}
	}
} 	

void run()
{
	clock_t start, end;
	double cpu_time_used;
	
	start = clock();
	
	smarandache();
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time = %lf s\n", cpu_time_used);
}

int main(int argc, char **argv)
{	
	mpz_init_set_si(a, 2);
	mpz_init(b);
	mpz_ui_pow_ui(b, 2, 1000000);
	primes = getPrimes(&length);
	getNumbers();
	
	if (argc != 2) return -1;
	
	threads = atoi(argv[1]);	
	omp_set_num_threads(threads);	
	run();
	
	mpz_clear(a);
	mpz_clear(b);
	free(numbers);
	return 0;
}
