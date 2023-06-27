#include "test_queue.h"

int enqueue(node * in, int val)
{
    printf("enqueue\n");
    if(in->index < max_size) 
    {
        in->value[in->index++] = val;
    }
    else
    {
        printf("queue is full\n");
    }
    
    return 0;
}

int dequeue(node * in)
{
    printf("dequeue\n");
    int ret = 0;

    if(in->index > 0)
    {
        ret = in->value[--in->index];
    }
    else
    {
        printf("queue is empty\n");
    }
    
    return ret;
}

void print_queue(node * in)
{
    if( in->index > 0) {
        for(unsigned int i=0; i < in->index; i++)
        {
            printf("value: %d\n", in->value[i]);
        }
    }
    else
    {
        printf("empty queue\n");
    }
    
}

int test_queue()
{
    node test;
    memset(test.value, 0, max_size * sizeof(int));
    printf("sizeof node: %lu\n", sizeof(node));
    print_queue(&test);
    enqueue(&test, 1);
    enqueue(&test, 5);
    print_queue(&test);
    printf("dequeue: %d\n", dequeue(&test));
    print_queue(&test);

    return 0;
}
