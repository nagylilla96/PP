#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>
#include <gmp.h>
#include <string.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

#define START 2
#define END ULLONG_MAX

int is_prime(const mpz_t x)
{
	mpz_t xx;
	mpz_init_set(xx, x);	
	mpz_t square, i;
	mpz_init(square);
	mpz_sqrt(square, xx);
	mpz_init_set_si(i, 2);
	
	while (mpz_cmp(i, square) <= 0)
	{
		mpz_t res;
		mpz_init(res);
		mpz_fdiv_r(res, x, i);
		if (mpz_cmp_si(res, 0) == 0)
		{
			return 0;
		}
		mpz_add_ui(i, i, 1);
	}
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
	return primes;
}

void print_results(vector<int> nums, int n)
{
	for (auto const& x : nums)
	{
		cout <<  x << " ";
	}
}

//void concatenate(mpz_t ret, mpz_t a, mpz_t b)
//{
//	mpz_t c, res;
//	mpz_init_set(c, b);
//	do
//	{
//		mpz_mul(a, a, 10);
//		mpz_fdiv_q(c, c, 10);
//	} while (c);
//	
//	mpz_init_set(res, a);
//	mpz_add(res, res, b);
//}

void smarandache(mpz_t a, mpz_t b)
{
	vector<int> primes = getPrimes();
	int index = 0;
	mpz_t conc;
	mpz_init_set_si(conc, 2);
	
	gmp_printf ("a = %Zd \n", a);
	gmp_printf ("b = %Zd \n", b);
	
	//cout << "EEEELO" << endl;

	if (mpz_cmp_ui(conc, 2) > 0) return;
	
	//cout << "EEEEEELO" << endl;
	
	for (auto const& x: primes)
	{
		//cout << "WHAT" << endl;
		if (mpz_cmp(conc, b) > 0)
		{
			//cout << "{" << conc.str() << "}";
			return;
		}
		if (is_prime(conc) && (mpz_cmp(conc, a) >= 0))
		{
			cout << ".";
			gmp_printf ("%Zd \n", conc);
		}
		char *mystr = (char*) malloc(1000);
		mpz_get_str(mystr, 10, conc);
		string str(mystr);
		strcpy(mystr, (str + to_string(x)).c_str());
		mpz_set_str(conc, mystr, 10);
		gmp_printf ("\n[%Zd]\n ", conc);	
	}
} 	

int main()
{
	mpz_t a;
	mpz_init_set_si(a, 2);
	mpz_t b;
	mpz_init_set_str(b, "2357111317192329313741434753596167717379838997101104", 10);
	//uint1024_t b = 100000;

	//print_results(getPrimes(), 100);

	vector<int> primes;

	try
	{
		auto start = chrono::high_resolution_clock::now();
		smarandache(a, b);
		auto finish = std::chrono::high_resolution_clock::now();
		cout << "Time = " << duration_cast<chrono::duration<double>>(finish - start).count() << " s" << endl;
	}
	catch (exception &e)
	{
		printf("%s\n", e.what());
	}
	
	cout << endl;

	//print_results(smars, smars.size());

	return 0;
}
