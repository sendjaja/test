#include "test_reverse_string.h"

void reverse_string(char* str)
{
        if(*str != 0)
        {
                reverse_string(str+1);
                printf("%c",*str);
        }
}

char* reverse_string2(const char *str)
{
        static char* temp=0;
        static int i=0;

        if(*str)
        {
                reverse_string2(str+1);
                temp = (char *)realloc(temp, ++i);
                *(temp+i) = 0;
                *(temp+(i-1)) = *str;
        }

        return temp;
}

int test_reverse_string()
{
        char test[11] = {'a', 'b', 'c', 'd', 'e', \
                         'f', 'g', 'h', 'i', 'j', '\0'};
        char* result;

        result = reverse_string2(test);

        puts(result);

        return 0;
}