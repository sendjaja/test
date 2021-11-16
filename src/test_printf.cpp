#include "test_printf.h"
#include <gtest/gtest.h>

void vector_print()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}

int test_helloworld()
{
    printf("Hello World\n");
    vector_print();
    return 0;
}
