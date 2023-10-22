#include "primes.h"

int main() {

	primes::isPrime(11) ? std::cout << "true\n" : std::cout << "false\n";
	primes::isPrime(15) ? std::cout << "true\n" : std::cout << "false\n";

	// now, given a number, determine how many brime integers before this number
	//std::cout << "Primes: " << primes::numberOfPrimesUntil(100) << std::endl;
		
	std::cout <<"Primes: " << primes::numberOfPrimesUntil(10) << std::endl;
	pthread_exit(nullptr);

	return 0;
}