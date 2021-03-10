#include <test_semaphore.h>

int test_semaphore()
{
    printf("Begin test_semaphore\n");
    sem_t *sem1 = sem_open("test_semaphore", O_CREAT, S_IRUSR | S_IWUSR, 0);
    // sem_t *sem2 = sem_open("test_semaphore", O_CREAT|O_EXCL, mode, value);

    if(sem1)
    {
        int pid = fork();

        if(pid == 0)
        {
            printf("child: test1\n");
            sem_post(sem1);
            // exit(0);
            printf("child: test2\n");
        }
        else
        {
            printf("parent: test1\n");
            // sleep(1);
            // wait(NULL);
            sem_wait(sem1);
            printf("parent: test2\n");
        }
    }
    else
    {
        printf("Fail in sem_open errno %d\n", errno);
    }

    // This test cause the next input to the choose test to be ignored
    return 0;
}