#include "test_bits.h"

void binprintf(int v)
{
    unsigned int mask=1<<((sizeof(int)<<3)-1);
    while(mask) {
        printf("%d", (v&mask ? 1 : 0));
        fflush(stdout); //add fflush to print to output right away
        mask >>= 1;
    }
}

int inspect_bits(unsigned int number)
{
    // Waiting to be implemented
    binprintf(number);
    printf(" = ");
    int ret = number & (number >> 1);
    // printf("%d\n", ret);
    return ret?1:0;
}

/* inspect bits 13 should return 1 since 1101 has 2 consecutive 1 */
int is_sequential_bits()
{
    printf("%d\n", inspect_bits(1));
    printf("%d\n", inspect_bits(2));
    printf("%d\n", inspect_bits(3));
    printf("%d\n", inspect_bits(4));
    printf("%d\n", inspect_bits(5));
    printf("%d\n", inspect_bits(6));
    printf("%d\n", inspect_bits(7));
    printf("%d\n", inspect_bits(8));
    printf("%d\n", inspect_bits(9));
    printf("%d\n", inspect_bits(10));
    printf("%d\n", inspect_bits(11));
    printf("%d\n", inspect_bits(12));
    printf("%d\n", inspect_bits(13));
    printf("%d\n", inspect_bits(14));
    return 0;
}

int test_bits()
{
    is_sequential_bits();
    return 0;
}