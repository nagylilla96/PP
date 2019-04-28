#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>
#include <gmp.h>
#include <string.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

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

vector<long long int> getPrimes()
{
	vector<long long int> primes;
	mpz_t i;
	mpz_init_set_si(i, 3);

	while (primes.size() < 2000)
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

void print_results(vector<long long int> nums, int n)
{
	for (auto const& x : nums)
	{
		cout <<  x << " ";
	}
}

void smarandache(mpz_t a, mpz_t b)
{
	vector<long long int> primes = getPrimes();
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
		if (mpz_probab_prime_p(conc, 15) == 2)
		{
			gmp_printf ("%Zd \n", conc);
		}
		
		char *mystr = (char*) malloc(1000);
		mpz_get_str(mystr, 10, conc);
		string str(mystr);
		strcpy(mystr, (str + to_string(x)).c_str());
		mpz_set_str(conc, mystr, 10);
		//gmp_printf ("\n[%Zd]\n ", conc);
		free(mystr);
	}
	mpz_clear(conc);
} 	

int main()
{
	mpz_t a;
	mpz_t b;
	
	mpz_init_set_si(a, 2);
	mpz_init(b);
	mpz_ui_pow_ui(b, 2, 1000000);

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
