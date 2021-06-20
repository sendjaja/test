#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "test_printf.h"
#include "test_queue.h"
#include "test_semaphore.h"
#include "test_oo_inheritance.h"
#include "test_unique_name.h"

// #define DEBUG

typedef struct testf {
    unsigned int index;
    const char *name;
    int (*test_function)();
} testf;

const unsigned int testCount = 5;

testf alltest[testCount] = {
    {0, "helloworld", test_helloworld},
    {1, "queue"     , test_queue},
    {2, "semaphore" , test_semaphore},
    {3, "OO inheritance", test_oo_inheritance},
    {4, "unique names", test_unique_name}
};

void print_choices()
{
    for(unsigned int i=0; i< testCount; i++) {
        printf("%d - %s\n", alltest[i].index, alltest[i].name);
    }
    printf("%lu - exit\n", sizeof(alltest)/sizeof(testf));
    printf("Choose test to run: ");
}

void clean_stdin(void)
{

    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main()
{
    char *buffer = NULL;
    int read;
    size_t len;
    do {
        print_choices();
        read = getline(&buffer, &len, stdin);
        if (-1 != read)
        {
#ifdef DEBUG
            puts(buffer);
#endif
            char *endptr;
            unsigned int i = strtol(buffer, &endptr, 10);

            if((*endptr == '\n') && (read > 1))
            {
                // Newline don't print Invalid choice, just ask for input again
                if(i < sizeof(alltest)/sizeof(testf))
                {
                    while(alltest[i].test_function() != 0);
                }
                else if(i == sizeof(alltest)/sizeof(testf))
                {
                    // Choosing number same as testCount is exit
                    break;
                }
                else
                {
                    // choice is bigger than testCount or negative
                    printf("Invalid test\n");
                }
            }
            else
            {
                // Choice is character then do nothing

                // If input is not newline print error
                // If input is newline, do not print error
                if(*endptr != '\n')
                    printf("Invalid choice\n");
            }
        }
        else
        {
            // This if is for handling Ctrl-D
            // in bash shell it's fine, in VSCode terminal, it keeps looping?
            if(*buffer == '\0')
                break;

            // When does this get executed?
            printf("No line read...\n");
            clean_stdin();
        }
#ifdef DEBUG
        printf("Size read: %d\n Len: %lu\n", read, len);
#endif
    }while(true);

    free(buffer);
    return 0;
}
