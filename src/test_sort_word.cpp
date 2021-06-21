#include "test_sort_word.h"

void sort_words(const char *words[], int count)
{
    int swap, nada = 0;
    // Waiting to be implemented
    for(int i = 0; i < count-1; i++)
    {
        for(int j = 0; (words[i][j]!=0) && (words[i+1][j]!=0);j++)
        {
            printf("compare i=%d %c and %c", i, words[i][j], words[i+1][j]);
            if(words[i][j] > words[i+1][j])
            {
                printf(" - nada\n"); nada++;
            }
            else
            {
                printf(" - swap\n"); swap++;
                //swap
                const char *temp = words[i];
                words[i] = words[i+1];
                words[i+1] = temp;
                i = -1;
            }
            break;
        }

        for(int k=0; k<count;k++)
            printf("%s\n", words[k]);
    }

    printf("swap = %d nada = %d\n", swap, nada);
}

/* Implement sorts array
 * Cherry orange apple, after sorting should be orange cherry apple 
 */
int test_sort_word()
{
    const char *words[] = { "cherry", "orange", "apple", "blueberry", "pineapple", "durian" };
    int count = 6;

    sort_words(words, count);

    for (int i = 0; i < count; i++)
    {
        printf("%s ", words[i]);
    }

    printf("\n");
    
    return 0;
}