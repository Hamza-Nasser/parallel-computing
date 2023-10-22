#pragma once
#ifndef PRIMES_H
#define PRIMES_H
constexpr auto NUM_THREADS = 5;
#include <pthread.h>
#include <iostream>
//#include <thread>

namespace primes
{
	// Function to check if a number is prime
	bool isPrime(int x);
	// Function to check if a number is prime (Enhanced version)
	bool isPrimeV2(int x);

	// Function to calculate the number of primes until a given target, basically using [NUM_THREADS] equal to 5
	int numberOfPrimesUntil(int target);
}

#endif
