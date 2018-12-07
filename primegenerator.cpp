#include "primegenerator.h"

PrimeGenerator::PrimeGenerator(): mutex()
{
    primes = {2, 3, 5, 7, 11, 13};
}

std::set<int> PrimeGenerator::getPrimesInterval(int first,int last)
{
	if (first > last)
		std::swap(first, last);
    auto itUp = primes.upper_bound(last);
    if (itUp == primes.end())
    {
        generatePrimes(last);
    }
	{
		std::lock_guard<std::mutex> guard(mutex);
		auto itLow = primes.lower_bound(first);
		itUp = primes.upper_bound(last);
		return{ itLow, itUp };
	}
}

void PrimeGenerator::generatePrimes(int limit)
{
    for(int i = *primes.rbegin() + 2; i <= limit; i += 2)
    {	
		std::lock_guard<std::mutex> guard(mutex);
        bool isPrime = true;
        int squareRoot = static_cast<int>(sqrt(i)) + 1;
        for (auto it = primes.begin(); it != primes.end() && (*it) <= squareRoot; ++it)
        {
            if(i % (*it) == 0)
            {
                isPrime = false;
                break;
            }
        }
        if (isPrime)
        {
            primes.insert(i);
        }
    }
}
