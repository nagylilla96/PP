#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>
#include <gmp.h>
#include <string.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

// TODO miller-rabin pseudo-prime algorithm https://www.geeksforgeeks.org/primality-test-set-3-miller-rabin/

#define START 2
#define END ULLONG_MAX

void power(mpz_t x, mpz_t y, const mpz_t p, mpz_t res)
{
	mpz_t temp;
	mpz_init(temp);
	mpz_set_si(res, 1);
	mpz_fdiv_q(x, x, p);
	while (mpz_cmp_d(y, 0) > 0)
	{
		if (mpz_odd_p(y) != 0)
		{
			mpz_mul(temp, res, x);
			mpz_fdiv_q(res, temp, p);
		}
		mpz_fdiv_q_2exp(y, y, 1);			
		mpz_mul(temp, x, x);
		mpz_fdiv_q(x, temp, p);		
	}
	mpz_clear(temp);
}

bool millerTest(mpz_t d, mpz_t n)
{
	mpz_t a, res, temp, n1;
	mpz_init_set_si(a, rand() % (INT_MAX - 2) + 2);
	mpz_init(res);
	mpz_init(temp);
	mpz_init(n1);
	
	cout << "---" << endl;
	
	mpz_sub_ui(n1, n, 1);
	
	power(a, d, n, res);
	
	if (mpz_cmp_d(res, 1) == 0 || mpz_cmp(res, n1) == 0)
	{
		mpz_clear(a);
		mpz_clear(res);
		mpz_clear(temp);
		mpz_clear(n1);
		return true;
	}
	
	cout << "---" << endl;
	
	while (mpz_cmp(d, n1) != 0)
	{
		cout << "---" << endl;
		mpz_mul(temp, res, res);
		mpz_fdiv_q(res, temp, n);
		mpz_mul_2exp(d, d, 1);
		
		if (mpz_cmp_d(res, 1) == 0) 
		{
			mpz_clear(a);
			mpz_clear(res);
			mpz_clear(temp);
			mpz_clear(n1);
			return false;
		}
		if (mpz_cmp(res, n1) == 0) 
		{
			mpz_clear(a);
			mpz_clear(res);
			mpz_clear(temp);
			mpz_clear(n1);
			return true;
		}
	}
	
	mpz_clear(a);
	mpz_clear(res);
	mpz_clear(temp);
	mpz_clear(n1);
	return false;
}

bool isPrime(mpz_t n, int k)
{
	
	if (mpz_cmp_d(n, 1) <= 0 || mpz_cmp_d(n, 4) == 0) return false;
	if (mpz_cmp_d(n, 3) <= 0) return true;
	
	mpz_t d, n1;
	mpz_init(n1);
	mpz_sub_ui(n1, n, 1);
	mpz_init_set(d, n1);
	mpz_clear(n1);
	
	
	
	while (mpz_odd_p(d) != 0)
	{
		mpz_fdiv_q_2exp(d, d, 1);	
	}
	
	cout << "---" << endl;
	
	for (int i = 0; i < k; i++) 
	{
		cout << "i = " << i << endl;
		if (!millerTest(d, n))
		{
			mpz_clear(d);
			
			return false;
		}
	}
	
	mpz_clear(d);
	
	return true;
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

// Get the first 100 primes
vector<int> getPrimes()
{
	vector<int> primes;
	mpz_t i;
	mpz_init_set_si(i, 3);

	while (primes.size() < 100)
	{
		if (is_prime(i))
		{
			primes.push_back(mpz_get_ui(i));
		}
		mpz_add_ui(i, i, 1);
	}
	mpz_clear(i);
	return primes;
}

void print_results(vector<int> nums, int n)
{
	for (auto const& x : nums)
	{
		cout <<  x << " ";
	}
}

void smarandache(mpz_t a, mpz_t b)
{
	vector<int> primes = getPrimes();
	mpz_t conc;
	mpz_init_set_si(conc, 2);
	

	if (mpz_cmp_ui(conc, 2) > 0) 
	{
		mpz_clear(conc);
		return;
	}
	
	for (auto const& x: primes)
	{
		
		if (mpz_cmp(conc, b) > 0)
		{
			
			mpz_clear(conc);
			return;
		}
		if (isPrime(conc, 5) && (mpz_cmp(conc, a) >= 0))
		{
			gmp_printf ("%Zd \n", conc);
		}
		
		char *mystr = (char*) malloc(1000);
		mpz_get_str(mystr, 10, conc);
		string str(mystr);
		strcpy(mystr, (str + to_string(x)).c_str());
		mpz_set_str(conc, mystr, 10);
		gmp_printf ("\n[%Zd]\n ", conc);
		free(mystr);
	}
	mpz_clear(conc);
} 	

int main()
{
	mpz_t a;
	mpz_t b;
	
	mpz_init_set_si(a, 2);
	mpz_init_set_str(b, "2357111317192329313741434753596167717379838997101102", 10);

	try
	{
		auto start = chrono::high_resolution_clock::now();
		smarandache(a, b);
		auto finish = std::chrono::high_resolution_clock::now();
		cout << "Time = " << duration_cast<chrono::duration<double>>(finish - start).count() << " s" << endl;
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
	}
	
	mpz_clear(a);
	mpz_clear(b);

	return 0;
}
