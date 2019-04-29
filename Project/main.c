#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <gmp.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

mpz_t a;
mpz_t b;
int threads;
unsigned long long int* primes;
int length;
mpz_t *numbers;

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

// Get the first primes
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

void smarandache(unsigned long long int *primes, int id)
{	
	printf("\nid = %d, threads = %d\n", id, threads); 
	
	for (int i = id; i < length; i += threads)
	{
		if (mpz_probab_prime_p(numbers[i], 15) == 2 && (mpz_cmp(numbers[i], a) >= 0))
		{
			gmp_printf("%Zd \n", numbers[i]);
		}
	}
} 	

void *threadFunc(void *args)
{
	int id = *((int*) args);
	
	smarandache(primes, id);
	
	printf("\nFinished running %d\n", id);	
	
	return NULL;
}

void run()
{
	clock_t start, end;
	double cpu_time_used;
	pthread_t* th = (pthread_t*) malloc(sizeof(pthread_t) * threads);
	
	start = clock();
	for (int i = 0; i < threads; i++) 
	{
		pthread_create(&th[i], NULL, threadFunc, &i);
		printf("Creating thread %d\n", i);
	}	
	for (int i = 0; i < threads; i++)
	{
		pthread_join(th[i], NULL);
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time = %lf s", cpu_time_used);
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
	run();

	//for (int i = 1; i <= 8; i++) 
	//{
	//	printf("\nRunning with %d threads!\n", i);
	//	threads = i;
	//	run(threads);
	//}
	
	mpz_clear(a);
	mpz_clear(b);
	free(numbers);
	return 0;
}
