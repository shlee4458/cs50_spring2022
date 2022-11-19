#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = 0;
    //take input between 1 and 8
    do
    {
        n = get_int("input numbers between 1 and 8: ");
    }
    while (n > 8 || n < 1);

    //for input 8 -> loop 7
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            //for n-i print " "
            if (j <= n - i)
            {
                printf(" ");
            }
            //for i print "#"
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }

}