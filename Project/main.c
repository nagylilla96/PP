#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <gmp.h>
#include <string.h>
#include <time.h>

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
			return 0;
		}
		mpz_add_ui(i, i, 1);
	}
	mpz_clear(square);
	mpz_clear(i);
	return 1;
}

// Get the first 100 primes
unsigned long int* getPrimes(int *n)
{
	unsigned long int *primes = (unsigned long int*) calloc(100, sizeof(unsigned long int));
	mpz_t i;
	mpz_init_set_si(i, 3);
	int size = 0;
	
	while (size < 100)
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

void print_results(unsigned long int* nums, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%lu ", nums[i]);
	}
}

void smarandache(mpz_t a, mpz_t b)
{
	int length = 0;
	unsigned long int* primes = getPrimes(&length);
	int index = 0;
	mpz_t conc;
	mpz_init_set_si(conc, 2);

	if (mpz_cmp_ui(conc, 2) > 0) return;
	
	for (int i = 0; i < length; i++)
	{
		if (mpz_cmp(conc, b) > 0)
		{
			mpz_clear(conc);
			return;
		}
		if (is_prime(conc) && (mpz_cmp(conc, a) >= 0))
		{
			gmp_printf("%Zd \n", conc);
		}
		char *mystr = (char*) malloc(1000);
		char *temp = (char*) malloc(1000);
		mpz_get_str(mystr, 10, conc);
		snprintf(temp, 1000, "%s%lu", mystr, primes[i]);
		strcpy(mystr, temp);
		mpz_set_str(conc, mystr, 10);
		//gmp_printf("\n[%Zd]\n ", conc);
	}
	mpz_clear(conc);
} 	

int main()
{
	mpz_t a;
	mpz_t b;
	clock_t start, end;
	double cpu_time_used;
	
	mpz_init_set_si(a, 2);
	mpz_init_set_str(b, "2357111317192329313741434753596167717379838997101103", 10);

	start = clock();
	smarandache(a, b);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time = %lf s", cpu_time_used);
	
	mpz_clear(a);
	mpz_clear(b);

	return 0;
}
