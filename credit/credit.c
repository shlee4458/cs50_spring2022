    #include <cs50.h>
    #include <stdio.h>

    long creditcard_number(void);
    long num_digits(long cn);
    long ammc_sldigit(long cn);
    long visa_firstdigit(long cn);
    long starting_value(long cn);
    long nd_card_type(long nd, long card_type1);
    long multi_two_sum(long cn, long nd);
    long validity_check(long mts);

    int main(void)
    {
        //get user input for credit card num
        long creditcard_num = creditcard_number();

        //record number of digits
        long num_digit = num_digits(creditcard_num);

        //card_type1 : matching starting value
        long card_type1 = starting_value(creditcard_num);

        //card_type2 : matching number of digits
        long card_type2 = nd_card_type(num_digit, card_type1);

        //summation of digits
        long sum_digits = multi_two_sum(creditcard_num, num_digit);

        //card_type3 : summation of digits
        long card_type3 = validity_check(sum_digits);

        //print final card type
        if (card_type1 == 4 || card_type2 == 4 || card_type3 == 4)
        {
            printf("INVALID\n");
        }
        else if (card_type1 == 1 && card_type2 == 1)
        {
            printf("AMEX\n");
        }
        else if (card_type1 == 2 && card_type2 == 2)
        {
            printf("MASTERCARD\n");
        }
        else if (card_type1 == 3 && card_type2 == 3)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    //prompt to input creditcard number
    long creditcard_number(void)
    {
        long n = 0;
        do
        {
            n = get_long("Input Your Credit Card Number: ");
        }
        while (n <= 0);
        return n;
    }

    //check number of digits :
    long num_digits(long cn)
    {
        int count = 1;

        do
        {
            cn = cn / 10;
            count = count + 1;
        }
        while (cn >= 10);
        return count;
    }

    //am, mc 2nd last digit
    long ammc_sldigit(long cn)
    {
        do
        {
            cn = cn / 10;
        }
        while (cn > 100);
        return cn;
    }

    //visa first digit
    long visa_firstdigit(long cn)
    {
        do
        {
            cn = cn / 10;
        }
        while (cn > 10);
        return cn;
    }

    //check starting value :
    //if 34 or 37 - AE, if 51,52,53,54,55 - MC, if 4 - Visa
    // 1 = AMEX, 2 = MC, 3= VISA, 4= INVALID, 5=VALID
    long starting_value(long cn)
    {
        long card_type1 = 0;
        if (ammc_sldigit(cn) == 34 || ammc_sldigit(cn) == 37)
        {
            card_type1 = 1;
        }
        else if (ammc_sldigit(cn) >= 51 && ammc_sldigit(cn) <= 55)
        {
            card_type1 = 2;
        }
        else if (visa_firstdigit(cn) == 4)
        {
            card_type1 = 3;
        }
        else
        {
            card_type1 = 4;
        }
        return card_type1;
    }

    //if 15 digits - AE, if 16 digits - MC, if 13/16 - Visa
    long nd_card_type(long nd, long card_type1)
    {
        long card_type2 = 0;
        if (nd == 15)
        {
            card_type2 = 1;
        }
        else if (nd == 16 && card_type1 == 2)
        {
            card_type2 = 2;
        }
        else if (nd == 13 || nd == 16)
        {
            card_type2 = 3;
        }
        else
        {
            card_type2 = 4;
        }
        return card_type2;
    }

    //check sum
    //multiply 2 to every digits excluding the last digit
    long multi_two_sum(long cn, long nd)
    {
        long dtt_sum = 0;
        long dtt = 0;

        for (int i = 1; i <= nd; i++)
        {
            if (i % 2 == 1)
            {
                dtt = cn % 10;
                dtt_sum = dtt_sum + dtt;
                cn = cn / 10;
            }
            else
            {
                dtt = cn % 10;
                dtt = dtt * 2;
                if (dtt >= 10)
                {
                    dtt_sum = dtt_sum + dtt / 10 + dtt % 10;
                    cn = cn / 10;
                }
                else
                {
                    dtt_sum = dtt_sum + dtt;
                    cn = cn / 10;
                }
            }
        }
        return dtt_sum;
    }

    //divide 10 and modulo =0 valid
    long validity_check(long mts)
    {
        long card_type3 = 0;

        if (mts % 10 == 0)
        {
            card_type3 = 5;
        }
        else
        {
            card_type3 = 4;
        }
        return card_type3;
    }
