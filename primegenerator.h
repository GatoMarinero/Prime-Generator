#ifndef PRIMEGENERATOR_H
#define PRIMEGENERATOR_H

#include <vector>
#include <set>
#include <math.h>
#include <mutex>

class PrimeGenerator
{
public:
    PrimeGenerator();
	std::set<int> getPrimesInterval(int first, int last);
private:
    void generatePrimes(int limit);
    std::set<int> foundPrimes;
    std::set<int> primes;
    mutable std::mutex mutex;
};

#endif // PRIMEGENERATOR_H
