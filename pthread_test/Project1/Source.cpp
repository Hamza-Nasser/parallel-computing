//#include<iostream>
//#include<pthread.h>
//#include <cstdint>
//void* worker(void *args) {
//	// Get thread id
//	//int tid = (int)args;
//	intptr_t tid = reinterpret_cast<intptr_t>(args);
//	std::cout << "Hello from thread number: "<<tid << std::endl;
//	std::cin.get();
//	return nullptr;
//}
//int main() {
//	pthread_t testThread;
//	intptr_t tid = 1;
//	/*__PTW32_DLLPORT int  __PTW32_CDECL pthread_create(pthread_t * tid,
//		const pthread_attr_t * attr,
//		void* (__PTW32_CDECL * start) (void*),
//		void* arg);*/
//
//	pthread_attr_t attr;
//
//	pthread_attr_init(&attr);
//
//	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
//
//	for (intptr_t  i = 0; i < 10; i++)
//	{
//		// create a joinable thread
//		
//		
//		int testThreadstate = pthread_create(&testThread,  &attr, worker, reinterpret_cast<void*>(i));
//		//pthreadCancelableTimedWait(&testThread, 10000);
//		pthread_join(testThread, nullptr); // equivalent to await, joinable thread only.
//		///Joinable thread, if success returns 0, else EAGAIN, [EAGAIN], [EFAULT], [EINVAL].
//		///is often raised when performing non-blocking I/O. 
//		///It means "there is no data available right now, try again later".
//		///[NOTE] Joinabale are mush like awaitable function, that other threads 
//		/// waits for it to complete its task.
//		if (testThreadstate != 0) {
//			std::cerr << "Thread creation failed." << std::endl;
//			return 1;
//		}
//	}
//	pthread_attr_destroy(&attr);
//
//	std::cin.get();
//	return 0;
//}

#include <iostream>
#include <pthread.h>
#include <semaphore.h>

sem_t a;
sem_t b;

void* task_A(void* arg)
{
    sem_wait(&a);
    std::cout << "A" << std::endl;
    sem_post(&a);
    return nullptr;
}

void* task_B(void* arg)
{
    sem_wait(&a);
    std::cout << "B" << std::endl;
    sem_post(&b);
    sem_post(&a);
    return nullptr;
}

void* task_C(void* arg)
{
    sem_wait(&b);
    std::cout << "C" << std::endl;
    sem_post(&a);
    return nullptr;
}

int main()
{
    pthread_t threadA, threadB, threadC;

    sem_init(&a, 0, 1); // Initialize semaphore 'a' to 1
    sem_init(&b, 0, 0); // Initialize semaphore 'b' to 0

    pthread_create(&threadA, nullptr, task_A, nullptr);
    pthread_create(&threadB, nullptr, task_B, nullptr);
    pthread_create(&threadC, nullptr, task_C, nullptr);

    pthread_join(threadA, nullptr);
    pthread_join(threadB, nullptr);
    pthread_join(threadC, nullptr);

    sem_destroy(&a);
    sem_destroy(&b);

    return 0;
}
