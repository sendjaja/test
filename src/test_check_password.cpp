#include "test_check_password.h"

#define exit(x) return(x)

#ifdef DEBUG
void odprintf(const char *format, ...)
{
    char    buf[4096], *p = buf;
    va_list args;
    int     n;

    va_start(args, format);
    n = vsnprintf(p, sizeof buf - 2 /*3*/, format, args); // buf-3 is room for CR/LF/NUL
    va_end(args);

    p += (n < 0) ? sizeof buf - 2 /*3*/ : n;

    while (p > buf  &&  isspace(p[-1]))
            *--p = '\0';

    // *p++ = '\r';
    *p++ = '\n';
    *p = '\0';

    printf("%s", buf);
}
#else
    void odprintf(const char *x, ...){}
#endif

int validate(const char *password)
{
    odprintf("password is %s", password);
    //check for len
    int len = strlen(password);

    odprintf("len = %lu", strlen(password));
    if (len < 12)
    {
            odprintf("length is less than 12 chars");
            exit(1);
    }

    //check that it has no "123"
    int seq_count = 4;
    for(int i=0; i<len  ; i++)
    {
        int match = 0;
        char char_to_compare = *(password+i);
        for(int j=0; j<seq_count && match < seq_count; j++)
        {
            //odprintf("? %c == %c :", *(password+i+j), char_to_compare+j);
            if(*(password+i+j) == char_to_compare+j)
            {
                match++;
                odprintf("%c ? %c %d == %c %d: Y",
                                *(password+i),
                                *(password+i+j),
                                *(password+i+j),
                                char_to_compare+j,
                                char_to_compare+j );
            }
            else
                odprintf("%c ? %c %d == %c %d: N",
                                *(password+i),
                                *(password+i+j),
                                *(password+i+j),
                                char_to_compare+j,
                                char_to_compare+j);
        }

        if(match == seq_count) {
            odprintf("Weak password");
            exit(1);
        }
    }

    int mix_letter_number = 0;
    //check that it has a mix of uppercase and lowercase
    for(int i='A'; i <= 'Z'; i++) {
        if(strchr(password, i))
        {
                odprintf("password has uppercase = %c\r\n", i);
                mix_letter_number++;
                break;
        }
        else
        {
                odprintf("password has no uppercase %c\r\n", i);
        }
    }

    for(int i='a'; i <= 'z'; i++) {
        if(strchr(password, i))
        {
            odprintf("password has lowercase = %c\r\n", i);
            mix_letter_number++;
            break;
        }
        else
        {
            odprintf("password has no lowercase %c\r\n", i);
        }
    }

    for(int i='0'; i <= '9'; i++) {
        if(strchr(password, i))
        {
            odprintf("password has number = %c\n", i);
            mix_letter_number++;
            break;
        }
        else
        {
            odprintf("password has no number %c\n", i);
        }
    }

    if(mix_letter_number == 3)
        exit(0);
    else
        exit(1);
}

int test_check_password()
{
    //Validate return 0 if strong, 1 if weak
    printf("Test Password\n");
    printf("%s\n", validate("Strong9Pssword")?"WEAK":"STRONG");     // Strong password
    printf("%s\n", validate("wstrong1password")?"WEAK":"STRONG");   // Weak  password
    printf("%s\n", validate("wstrong")?"WEAK":"STRONG");                   // Weak  password
    printf("%s\n", validate("wstrong123password")?"WEAK":"STRONG"); // Weak  password

    return 0;
}
