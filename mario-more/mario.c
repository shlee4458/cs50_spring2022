#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = 0;
    //prompt to put numbers between 1 to 8
    do
    {
        n = get_int("input a number between 1 and 8: ");
    }
    while (n < 1 || n > 8);

    //for each row add a line
    for (int i = 1; i <= n; i++)
    {
        //for j<n-i print blank
        for (int j = 1; j <= n - i; j++)
        {
            printf(" ");
        }

        //print i number of #
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }

        //print 2 blanks
        for (int k = 1; k < 3; k++)
        {
            printf(" ");
        }

        //print i number of #
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }

        //add an escape for every row
        printf("\n");

    }
}