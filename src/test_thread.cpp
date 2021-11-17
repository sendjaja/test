#include "test_thread.h"

void * run(void * arg)
{
    (void)arg;
    printf("thread running\n");

    return NULL;
}

int test_thread()
{
    printf("test thread\n");

    int status = 0;
    pthread_t tid;

    status = pthread_create(&tid, NULL, &run, NULL);
    // Check if thread is created sucessfuly
	if (status)
	{
		std::cout << "Thread creation failed : " << strerror(status);
		return status;
	}
	else
		std::cout << "Thread Created with ID : " << tid << std::endl;

    std::cout << "Waiting for thread to exit" << std::endl;
	// Wait for thread to exit
	status = pthread_join(tid, NULL);

	// check if joining is sucessful
	if (status)
	{
		std::cout << "Failed to join Thread : " << strerror(status) << std::endl;
		return status;
	}

	std::cout << "Exiting Main" << std::endl;

    return 0;
}