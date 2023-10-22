#include "primes.h"
namespace primes {
    pthread_mutex_t mtx;  // Mutex for protecting shared data
    int finalPrimes = 0;
    int workerLength = 0;
    bool isPrime(int x) {
        if (x <= 1) {
            return false;
        }
        for (int i = 2; i <= x / 2; i++)
        {
            if (x % i == 0) {
                return false;
            }
        }
        return true;
    }
    bool isPrimeV2(int x) {
        if (x <= 1) {
            return false;
        }
        if (x <= 3) {
            return true;
        }
        if (x % 2 == 0 || x % 3 == 0) {
            return false;
        }
        for (int i = 5; i * i <= x; i += 6) {
            if (x % i == 0 || x % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }

    static void* worker(void* args) {
        intptr_t tid = reinterpret_cast<intptr_t>(args);
        int start = tid * workerLength;
        int end = start + workerLength;

        int primes = 0;
        for (int i = start; i < end; i++) {
            if (isPrimeV2(i)) {
                primes++;
            }
        }

        pthread_mutex_lock(&mtx);
        std::cout << "partial primes: " << primes << std::endl;
        finalPrimes += primes;
        pthread_mutex_unlock(&mtx);

        return nullptr;
    }

    int numberOfPrimesUntil(int target) {
        //workerLength = target / std::thread::hardware_concurrency(); 
        // Determine the number of threads to use based on the number of cores available in runtime

        workerLength = target / NUM_THREADS;
        pthread_t threads[NUM_THREADS]{};

        if (pthread_mutex_init(&mtx, nullptr) != 0) {
            std::cerr << "Mutex initialization failed" << std::endl;
            return -1;
        }

        for (intptr_t i = 0; i < NUM_THREADS; i++) {
            if (pthread_create(&threads[i], nullptr, worker, reinterpret_cast<void*>(i)) != 0) {
                std::cerr << "Thread creation failed" << std::endl;
                return -1;
            }
        }

        for (intptr_t i = 0; i < NUM_THREADS; i++) {
            if (pthread_join(threads[i], nullptr) != 0) {
                std::cerr << "Thread join failed" << std::endl;
                return -1;
            }
        }

        pthread_mutex_destroy(&mtx);

        return finalPrimes;
    }

}