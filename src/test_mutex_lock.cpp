#include "test_mutex_lock.h"

static mutex myMutex, myMutex1, myMutex2, myMutex3, myMutex4;

void shared_cout(int i)
{
        //lock_guard<mutex> g(myMutex);
        //myMutex.lock();
    cout << " " << i << " ";
    //myMutex.unlock();
}

void f(int n)
{
        lock_guard<mutex> lock(myMutex);
        for(int i = 10*(n-1); i < 10*n ; i++) {
        shared_cout(i);
    }

}

int test_mutex_lock(void)
{
    thread t1(f, 1);  // 0-9
    thread t2(f, 2);  // 10-19
    thread t3(f, 3);  // 20-29
    thread t4(f, 4);  // 30-39
    thread t5(f, 5);  // 40-49

    //Calling lock here will cause deadlock
    //lock_guard<mutex> lock(myMutex);
    //These 2 line below, printing 0 to -49 can get preempted since it is not
    //protected by mutex
    //for(int i = 0; i > -50; i--)
    //    shared_cout(i);  // (0, -49)
    f(6);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}
