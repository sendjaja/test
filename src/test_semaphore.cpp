#include "test_semaphore.h"

void endProcess()
{
    printf("exit\n");
}

int test_semaphore()
{
    printf("Begin test_semaphore\n");
    sem_t *sem1 = sem_open("test_semaphore", O_CREAT, S_IRUSR | S_IWUSR, 0);
    sem_t *sem2 = sem_open("test_semaphore", O_CREAT, S_IRUSR | S_IWUSR, 0);
    int pid = 0;

    if(sem1 && sem2)
    {
        // getppid will return either the shell pid or gdb/lldb pid
        printf("Before fork\t pid:%d ppid:%d\n", getpid(), getppid());
        pid = fork();

        if(pid == 0)
        {
            printf("child1\t\t pid:%d ppid:%d\n", getpid(), getppid());
            sem_post(sem1);
            printf("child2\n");

            atexit(endProcess);
            // exit function will call endProcess
            exit(0);

            // _exit function will not call endProcess
            // _exit(0);
        }
        else
        {
            int status;
            printf("parent1\t\t pid:%d ppid:%d\n", getpid(), getppid());
            sem_wait(sem1);
            printf("parent2\n");
            (void)waitpid(pid, &status, 0);
        }
    }
    else
    {
        printf("Fail in sem_open errno %d\n", errno);
    }

    return 0;
}
