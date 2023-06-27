#ifndef TEST_SEMAPHORE_H
#define TEST_SEMAPHORE_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <cstdlib>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int test_semaphore();

#endif