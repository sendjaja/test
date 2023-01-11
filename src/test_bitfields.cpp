#include "test_bitfields.h"
#include <string>
using namespace std;

typedef struct __attribute__((packed)) {
    unsigned char test1:1, // 0000 000X
                  test2:7; // XXXX XXX0
} packed_data_t;

int test_bitfields()
{
    packed_data_t t;
    // declaring t.test1 to other than 0 or 1 will result in compile error
    t.test1 = 0x0;
    // Max is 7F because 7 bits
    t.test2 = 0x7F;

    printf("sizeof(t)=%lu test1=%x test2=%x\n", sizeof(t), t.test1, t.test2);
    printf("Address of t = %p\n", &t);

    // bitfields member are not addressable, thus 2 lines below cannot be compiled
    // printf("Address of t.test1 = %p\n", &(t.test1));
    // printf("Address of t.test2 = %p\n", &(t.test2));

    // should print 0xFE
    printf("value on address = 0x%X\n", *((unsigned char *)&t));

    t.test1 = 0x1;

    printf("sizeof(t)=%lu test1=%x test2=%x\n", sizeof(t), t.test1, t.test2);
    printf("Address of t = %p\n", &t);

    // should print 0xFF
    printf("value on address = 0x%X\n", *((unsigned char *)&t));

    return 0;
}