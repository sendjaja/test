#ifndef TESTF_H
#define TESTF_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef struct testf {
    unsigned int index;
    const char *name;
    int (*test_function)();
} testf;

#endif