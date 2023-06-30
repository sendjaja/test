// test struct used internally
#include "testf.h"

// test cases
#include "test_printf.h"
#include "test_queue.h"
#include "test_semaphore.h"
#include "test_oo_inheritance.h"
#include "test_unique_name.h"
#include "test_quadratic_equation.h"
#include "test_sort_word.h"
#include "test_bits.h"
#include "test_overload_function.h"
#include "test_struct.h"
#include "test_thread.h"
#include "test_generate_password_CPlusPlus.h"
#include "test_generate_password_C.h"
#include "test_2darray.h"
#include "test_bitfields.h"
#include "test_fibonacci.h"
#include "test_pthread_printf.h"

// List of tests
testf alltest[] = {
    { 0,              "helloworld", test_helloworld                 },
    { 1,              "queue"     , test_queue                      },
    { 2,              "semaphore" , test_semaphore                  },
    { 3,          "OO inheritance", test_oo_inheritance             },
    { 4,            "unique names", test_unique_name                },
    { 5,      "quadratic equation", test_quadratic_equation         },
    { 6,               "sort word", test_sort_word                  },
    { 7,                    "bits", test_bits                       },
    { 8,       "overload function", test_overload_function          },
    { 9,                  "struct", test_struct                     },
    {10,                 "threads", test_thread                     },
    {11,   "generate password C++", test_generate_password_CPlusPlus},
    {12,     "generate password C", test_generate_password_C        },
    {13,                 "2darray", test_2darray                    },
    {14,               "bitfields", test_bitfields                  },
    {15,               "fibonacci", test_fibonacci                  },
    {16,          "pthread_printf", test_pthread_printf             }
};

unsigned int testCount = sizeof(alltest)/sizeof(testf);

// Print all the tests
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

// Call test if it's valid
int call_test(unsigned long i)
{
    if(i < sizeof(alltest)/sizeof(testf))
    {
        // Call the test function
        printf("test %s\n", alltest[i].name);
        alltest[i].test_function();
    }
    else if(i == sizeof(alltest)/sizeof(testf))
    {
        // Choosing number same as testCount is exit
        return -1;
    }
    else
    {
        // choice is bigger than testCount or negative
        printf("Invalid test\n");
    }

    return 0;
}

int menu(long choice)
{
#ifdef __APPLE__
    ssize_t read = 0;
#else
    int read = 0;
#endif

    size_t len = 0;

    if(choice < 0)
    {
        char *buffer = NULL;
        char *endptr;
        unsigned long i = 0;
        while(true)
        {
            print_choices();
            read = getline(&buffer, &len, stdin);
            printf("Selection: ");
            puts(buffer);
            i = strtoul(buffer, &endptr, 10);
            if (-1 != read)
            {
                if((*endptr == '\n') && (read > 1))
                {
                    // Newline don't print Invalid choice, just ask for input again
                    if( call_test(i)==-1 )
                        break;
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
        }

        if(buffer)
            free(buffer);
    }
    else
    {
        std::cout << "Selection: " << choice << std::endl;
        if(call_test(choice)==-1)
            exit(0);
    }

#if DEBUG == 1
#ifdef __APPLE__
        printf("Size read: %zd\nLen: %lu\n", read, len);
#else
        printf("Size read: %d\nLen: %lu\n", read, len);
#endif
#endif // DEBUG

    return 0;
}

#if DEBUG == 0
int main(int argc, const char * argv[]) {
    if(argc > 2)
    {
        cout << "too many arguments" << endl;
        return -1;
    }
    else if(argc == 2)
    {
        // check for char in argv[1]
        for(int j=0; argv[1][j] != 0; j++)
        {
            if (!isdigit(argv[1][j]))
            {
                cout << "invalid argument" << endl;
                return -1;
            }
        }

        unsigned long i = strtoul(argv[1], NULL, 10);
        // check errno for empty input, ""
        if(errno != 0)
        {
            cout << "invalid argument" << endl;
            return -1;
        }
        else
            menu(i);
    }
    else
    {
        // input -1 to menu() for letting user select which
        // test to run manually
        menu(-1);
    }

    return 0;
}
#else  //ifndef DEBUG

#include <gtest/gtest.h>

TEST(TestAll, test)
{
    for(unsigned long i = 0; i < testCount; i++)
    {
        EXPECT_EQ(0, menu(i));
    }
}

// If DEBUG is defined, use google test to run all test
int main(int argc, const char * argv[]) {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}

#endif // ifndef DEBUG
