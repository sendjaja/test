#ifndef TEST_QUEUE_H
#define TEST_QUEUE_H

#include <stdio.h>
#include <string.h>

const unsigned int max_size = 100;

typedef struct node{
    int value[max_size];
    unsigned int index = 0;
} node;

int test_queue();

#endif