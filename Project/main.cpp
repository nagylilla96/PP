#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>
#include <gmp.h>
#include <string.h>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

vector<unsigned long long int> primes;
mpz_t *numbers;
mpz_t a, b;
int length;
int threads;

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

vector<unsigned long long int> getPrimes()
{
	vector<unsigned long long int> primes;
	mpz_t i;
	mpz_init_set_si(i, 3);
	length = 0;

	while (primes.size() < 2000)
	{
		if (is_prime(i))
		{
			primes.push_back(mpz_get_ui(i));
			length++;
		}
		mpz_add_ui(i, i, 1);
	}
	mpz_clear(i);
	return primes;
}

void print_results(vector<unsigned long long int> nums, int n)
{
	for (auto const& x : nums)
	{
		cout <<  x << " ";
	}
}

void getNumbers()
{
	
	numbers = (mpz_t*) malloc(sizeof(mpz_t) * length);
	
	mpz_t conc;
	mpz_init_set_si(conc, 2);	
	int i = 0;

	if (mpz_cmp_ui(conc, 2) > 0) 
	{
		mpz_clear(conc);
		return;
	}
	
	for (auto const& x: primes)
	{
		//cout << "FASZ" << endl;
		if (mpz_cmp(conc, b) > 0)
		{			
			//cout << "FASZ" << endl;
			mpz_clear(conc);
			return;
		}		
		//gmp_printf("[%Zd] \n", conc);
		mpz_init_set(numbers[i], conc);
		
		char *mystr = (char*) malloc(10000);
		mpz_get_str(mystr, 10, conc);		
		string str(mystr);
		strcpy(mystr, (str + to_string(x)).c_str());
		mpz_set_str(conc, mystr, 10);		
		free(mystr);
		i++;
	}
	mpz_clear(conc);
}	

class Runner 
{
public:
	void smarandache(int id)
	{
		//cout << "id = " << id << ", threads = " << threads << endl;
		for (int i = id; i < length; i += threads)
		{
			if (mpz_probab_prime_p(numbers[i], 15) == 1 && (mpz_cmp(numbers[i], a) >= 0))
			{
				gmp_printf("%Zd \n", numbers[i]);
			}
		}
	} 
};

void run()
{
	Runner *runner = new Runner();
	auto start = chrono::high_resolution_clock::now();
	vector<thread> v;
	
	for (int i = 0; i < threads; i++)
	{
		//cout << "Creating thread " << i << endl;
		v.push_back(thread(&Runner::smarandache, runner, i));
	}
	for(auto & th: v)
	{
		th.join();
	}
	auto finish = std::chrono::high_resolution_clock::now();
	cout << "Time = " << duration_cast<chrono::duration<double>>(finish - start).count() << " s" << endl;
	delete runner;
}

int main()
{
	
	mpz_init_set_si(a, 2);
	mpz_init(b);
	mpz_ui_pow_ui(b, 2, 1000000);
	primes = getPrimes();
	getNumbers();

	for (int i = 1; i <= 8; i++)
	{
		try
		{
			cout << "Running with " << i << " threads!" << endl;
			threads = i;
			run();
		}
		catch (exception &e)
		{
			cout << e.what() << endl;
		}
	}
	
	mpz_clear(a);
	mpz_clear(b);

	return 0;
}
