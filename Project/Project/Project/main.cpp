#include <iostream>
#include <vector>
using namespace std;

int is_prime(int x)
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

void print_primes(vector<int> primes, int n)
{
	for (auto const& x : primes)
	{
		cout << x << " ";
	}
}

int concat(int a, int b)
{
	int c = b;
	do
	{
		a *= 10;
		c /= 10;
	} while (c);

	return a + b;
}

vector<int> smarandache(int b)
{
	vector<int> numbers;
	int index = 0;
	int prime = 2;

	if (b < 2) return numbers;

	numbers.push_back(prime);

	while (numbers.at(index) <= b)
	{
		prime++;
		if (is_prime(prime))
		{
			int concated = concat(numbers.at(index), prime);
			if (is_prime(concated))
			{
				numbers.push_back(concated);
				index++;
			}
		}
	}

}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << "Usage: main.exe <start> <end>" << endl;
		return -1;
	}

	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int nr;
	vector<int> primes;

	if (a > b)
	{
		int c = b;
		b = a;
		a = c;
	}

	primes = getPrimes();

	print_primes(primes, primes.size());

	return 0;
}