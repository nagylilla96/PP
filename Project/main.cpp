#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/lexical_cast.hpp>
using namespace std;
using boost::multiprecision::uint1024_t;

#define START 2
#define END ULLONG_MAX

int is_prime(uint1024_t x)
{
	for (uint1024_t i = 2; i <= x / 2; i++)
	{
		if (x % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

// Get the first 100 primes
vector<int> getPrimes()
{
	vector<int> primes;
	int i = 2;

	while (primes.size() < 100)
	{
		if (is_prime(i))
		{
			primes.push_back(i);
		}
		i++;
	}
	return primes;
}

void print_results(vector<uint1024_t> nums, int n)
{
	for (auto const& x : nums)
	{
		cout << (uint1024_t) x << " ";
	}
}

uint1024_t concat(uint1024_t a, uint1024_t b)
{
	uint1024_t c = b;
	do
	{
		a *= 10;
		c /= 10;
	} while (c);

	return a + b;
}

void smarandache(uint1024_t a, uint1024_t b)
{
	vector<int> primes = getPrimes();
	uint1024_t limit = (uint1024_t(1) << 1024) - 1;
	int index = 0;
	uint1024_t conc = primes.at(index);

	if (b < 2) return;
	
	for (auto const& x: primes)
	{
		if (conc > b)
		{
			cout << "{" << conc.str() << "}";
			return;
		}
		if (is_prime(conc) && (conc >= a))
		{
			cout << conc.str() << " ";
		}
		conc = boost::lexical_cast<uint1024_t>(conc.str() + to_string(primes.at(++index)));
		cout << "[" << conc.str() << "]";
		
	}
}

int main(int argc, char** argv)
{
	uint1024_t a;
	uint1024_t b;
	uint1024_t limit = (uint1024_t(1) << 1024) - 1;
	
	cout << "Limit: " << limit.str() << endl;

	if (argc != 3)
	{
		if (argc == 1)
		{
			a = START;
			b = END;
		}
		else
		{
			cout << "Usage: main.exe <start> <end>" << endl;
			return -1;
		}
	}

	string::size_type sz = 0;
	a = boost::lexical_cast<uint1024_t>(argv[1]);
	b = boost::lexical_cast<uint1024_t>(argv[2]);
	vector<int> primes;
	vector<uint1024_t> smars;

	if (a > b)
	{
		uint1024_t c = b;
		b = a;
		a = c;
	}
	
	b = (uint1024_t(1) << 1024) - 1;

	try
	{
		smarandache(a, b);
	}
	catch (exception &e)
	{
		printf("%s\n", e.what());
	}
	
	cout << endl;

	//print_results(smars, smars.size());

	return 0;
}
