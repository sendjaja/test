#include "test_generate_password_C.h"

char password[16] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};

bool isamatch(long long * pass)
{
   printf("pass = %p\n", pass);

    for(int j=0; j< 16; j++)
    {
//        printf("%04llx ", pass[j]);
    }
    printf("\n");

    return true;
}

bool print_one_line(unsigned char * val) {
    // print the 16 char array
    for(int l=0; l < 16; l++)
        printf("%02x ", val[l]);
    printf("\n");
    // end of print the 16 char array

    if(val[14] == 0xff && val[15] == 0xff)
        return true;

    return false;
}

void print_all(void) {
    int base = 0x100, exp = NUM_OF_CHAR;
    long long result = 1;

    while (exp != 0) {
            result *= base;
            --exp;
    }

    printf("total possibilities = %lld\n", result);

/*
#ifdef USE_LONG_LONG
    long long val[16] = {0};

    for (long long i = 0 ; i < result; i++) {
        printf("%04llx ", i);
        val[i%16] = i;

        if(((i+1)%16) == 0)
        {
            printf("\n");
//            isamatch(val);
        }
    }
#endif
*/

    /*
     00 00 00 00
     00 00 00 01
     00 00 00 02
     .
     .
     .
     00 00 00 ff

     00 00 01 00
     00 00 01 01
     00 00 01 02
     .
     .
     .
     00 00 01 ff
     00 00 02 00
     */
    unsigned char val[16] = {0};

    for(int i = 0; i < NUM_OF_CHAR ; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            for(int k = 0; k < 256; k++) {
                /*
                if(i!=0)
                {
                    val[15-j]++;
                    i = 0;
                }
                 */
                if(print_one_line(val) == true)
                {
//                    exit(-1);
                    continue;
                }
                val[15-j]++;
            }
        }
    }
}

unsigned char val1[16] = {0};

void test1(int j, unsigned char * val1) {
    for(int k = 0; k < 256; k++) {
        print_one_line(val1);
        val1[15-j]++;
    }
}

void test(void) {
    for(int i = 0; i < 16; ) {
        for( int j = 0; j <= i; j++) {
            printf("i=%d j=%d\n", i, j);
            val1[15-i] = i;

            for(int k = 0; k < 256; k++) {
                val1[15-j]++;
//                print_one_line(val1);
            }
//            test1(j, val1);
        }
        printf("\n");
        i++;
    }

}

/*
 Works to print 00 - ff
 to keep increasing, needs recursion

 GenerateAllPasswords(pwd,pos,siz)
    if(pos<siz)
        foreach(char ch in chars)
            GenerateAllPasswords(pwd+ch,pos+1,siz);
        next
    else
        print pwd;
    endif
 */
void test2(void) {
    for(int a = 0; a < 16; ) {
        for(int b = 0; b < 16; ) {
            for(int c = 0; c < 16; c++) {
                printf("a=%02d;b=%02d;c=%02d - %03x\n", a, b, c, a<<8 | b<<4 | c);
            }
            b++;
        }
        a++;
    }

}

void test3(void) {
    int base = 256, exp = NUM_OF_CHAR;
    double result = 1;

    while (exp != 0) {
            result *= base;
            --exp;
    }

    printf("total possibilities = %15.64g\n", result);
    printf("FLT_MAX             = %15.64g\n", (float) FLT_MAX);
    /*
    for(int i = 0; i < result; i++) {
        unsigned char theword[16] = {0};
        int val = i;
        for(int j = 0; j < 16; j++)
        {
            int ch = val % base;
            theword[15-j] = ch;
            val = val / base;
        }
        print_one_line(theword);
    }
     */
}

/*
 1 char = 2^8 = 256
 2 char = (2^8) ^ 2 = 65536
 3 char = (2^8) ^ 3 = 16777216
 ...
 ...
 16 char = (2^8) ^ 16 = 3.402823669209385e38

 64 bit 8 bytes max is only 1.8446744073709551615e19
 */
// int main(int argc, const char * argv[]) {
//     printf("Start\n");
// //    print_all();
//     test3();
//     printf("End\n");
//     return 0;
// }

int test_generate_password_C()
{
    printf("Start\n");
//    print_all();
    test3();
    printf("End\n");
    return 0;
    return 0;
}
