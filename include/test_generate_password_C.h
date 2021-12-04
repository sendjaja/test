#ifndef TEST_GENERATE_PASSWORD_C_H
#define TEST_GENERATE_PASSWORD_C_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>

#define NUM_OF_CHAR 16
#define PRINT_WIDTH 8

#ifdef __cplusplus
// the C++ compiler will see this causing all declarations in the block to have C linkage,
// the C compiler won't see it (skipped by the preprocessor)
extern "C" {
#endif

int test_generate_password_C();

#ifdef __cplusplus
}
#endif

#endif