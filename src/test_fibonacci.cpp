// References is from https://learn.arm.com/learning-paths/microcontrollers/rpi_pico/perf/
//

#include "test_fibonacci.h"

#define SECS_IN_DAY (24 * 60 * 60)

static struct timespec  ts;
static struct timespec  te;
static struct timespec  tr;

static void start_systick()
{    
    clock_gettime(CLOCK_MONOTONIC, &ts);
}

static void stop_systick()
{    
    clock_gettime(CLOCK_MONOTONIC, &te);
}

static void timespec_diff(struct timespec *start, struct timespec *stop,
                   struct timespec *result)
{
    if ((stop->tv_nsec - start->tv_nsec) < 0) {
        result->tv_sec = stop->tv_sec - start->tv_sec - 1;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        result->tv_sec = stop->tv_sec - start->tv_sec;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec;
    }

    return;
}

int fib1(int count)
{
    int first_term = 0, second_term = 1, next_term;

    printf("First Fibonacci series\n");

    (void) start_systick();

    for (int i = 0; i < count ; i++ )
    {
        if ( i <= 1 )
           next_term = i;
        else
        {
            next_term = first_term + second_term;
            first_term = second_term;
            second_term = next_term;
        }
        printf("%d\n",next_term);
    }

    (void) stop_systick();

    timespec_diff(&ts, &te, &tr);

    printf("First Fibonacci series complete: %ld ns\n", tr.tv_nsec);

    return 0;
}

int fibonacci_series(int num)
{
    if (num == 0)
        return 0;
    else if (num == 1)
        return 1;
    else
        return (fibonacci_series(num-1) + fibonacci_series(num-2));
}

int fib2(int count)
{
    int c = 0;

    printf("Second Fibonacci series\n");

    (void) start_systick();

    for (int i = 1; i <= count ; i++ )
    {
        fibonacci_series(c);
        printf("%d\n", fibonacci_series(c));
        c++;
    }

    (void) stop_systick();

    timespec_diff(&ts, &te, &tr);

    printf("Second Fibonacci series complete: %ld ns\n", tr.tv_nsec);

    return 0;
}

static void displayClock(clockid_t clock, const char *name, bool showRes)
{
    long             days;
    struct timespec  ts;

    if (clock_gettime(clock, &ts) == -1) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }

    printf("%-15s: %10jd.%03ld (", name,
            (intmax_t) ts.tv_sec, ts.tv_nsec / 1000000);

    days = ts.tv_sec / SECS_IN_DAY;
    if (days > 0)
        printf("%ld days + ", days);

    printf("%2dh %2dm %2ds",
            (int) (ts.tv_sec % SECS_IN_DAY) / 3600,
            (int) (ts.tv_sec % 3600) / 60,
            (int) ts.tv_sec % 60);
    printf(")\n");

    if (clock_getres(clock, &ts) == -1) {
        perror("clock_getres");
        exit(EXIT_FAILURE);
    }

    if (showRes)
        printf("     resolution: %10jd.%09ld\n",
                (intmax_t) ts.tv_sec, ts.tv_nsec);
}

int test_fibonacci()
{
    int count = 25;
    int ret = 0;
    bool showRes = true;
    
    displayClock(CLOCK_MONOTONIC, "CLOCK_MONOTONIC", showRes);

    ret |= fib1(count);

    ret |= fib2(count);

    return ret;
}
