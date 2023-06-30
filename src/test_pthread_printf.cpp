#include "test_pthread_printf.h"

void *print_message_function( void *ptr );

struct time_and_string {
    timespec time_start, time_end;
    const char *msg;
};

int test_pthread_printf() {
    pthread_t thread1, thread2;
    struct timespec t1;
    const char *message1 = "Thread 1";
    const char *message2 = "Thread 2";
    int  iret1, iret2;
    struct time_and_string ts1, ts2;
    clock_gettime(CLOCK_MONOTONIC, &t1);

    /* Test with valgrind
        * uncomment to show valgrind error */
    //  char* p1 = new char[15];
    // delete(p1);

    ts1.msg = message1;
    ts1.time_start = t1;
    ts2.msg = message2;
    ts2.time_start = t1;

    cout << "Creating thread at:" << ts1.time_start.tv_sec << "." <<
                    ts1.time_start.tv_nsec<< endl;

    /* Create independent threads each of which will execute function */
    iret1 = pthread_create( &thread1, NULL, print_message_function,
                                                (void*) &ts1);
    iret2 = pthread_create( &thread2, NULL, print_message_function,
                                                (void*) &ts2);

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */

    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);

    cout << "thread 1 returns:" << iret1 << " " << ts1.time_end.tv_sec << "."
                    << ts1.time_end.tv_nsec<< endl;
    cout << "thread 2 returns:" << iret2 << " " << ts2.time_end.tv_sec << "."
                    << ts2.time_end.tv_nsec<< endl;
    return 0;
}

void *print_message_function(void *ptr)
{
        struct time_and_string *temp = (struct time_and_string *)ptr;
        clock_gettime(CLOCK_MONOTONIC, &temp->time_end);
        unsigned long long diff = temp->time_end.tv_nsec - temp->time_start.tv_nsec;
        printf("tid:%ld time diff :%llu\n", pthread_self(), diff);
        return (void *) temp;
}