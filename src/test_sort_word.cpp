#include "test_sort_word.h"

void sort_words(const char *words[], int count)
{
    int swap = 0, nada = 0;
    // Waiting to be implemented
    for(int i = 0; i < count-1; i++)
    {
        printf("compare i=%d %c and %c", i, words[i][0], words[i+1][0]);
        if(words[i][0] > words[i+1][0])
        {
            printf(" - nada\n"); nada++;
        }
        else if(words[i][0] < words[i+1][0])
        {
            printf(" - swap\n"); swap++;
            //swap
            const char *temp = words[i];
            words[i] = words[i+1];
            words[i+1] = temp;
            i = -1;
        }
        else
        {
        
            for(int j = 1; (words[i][j]!=0) && (words[i+1][j]!=0);j++)
            {
                printf("compare i=%d j=%d %c and %c", i, j, words[i][j], words[i+1][j]);
                if(words[i][j] > words[i+1][j])
                {
                    printf(" - nada\n"); nada++;
                    break;
                }
                else if(words[i][j]  < words[i+1][j])
                {
                    printf(" - swap\n"); swap++;
                    //swap
                    const char *temp = words[i];
                    words[i] = words[i+1];
                    words[i+1] = temp;
                    i = -1;
                    break;
                }
                else
                {
                    printf(" - continue\n");
                }
            }
        }

        for(int k=0; k<count;k++)
            printf("%s ", words[k]);
        printf("\n");
    }

    printf("swap = %d nada = %d\n", swap, nada);
}

/* Implement sorts array
 * Cherry orange apple, after sorting should be orange cherry apple 
 */
int test_sort_word()
{
    const char *words[] = { "cherry", "orange", "apple", "blueberry", "pineapple", "pipaya" };
    int count = 6;

    sort_words(words, count);

    printf("Sorted result: \n");
    for (int i = 0; i < count; i++)
    {
        printf("%s ", words[i]);
    }
    printf("\n");
    
    return 0;
}
