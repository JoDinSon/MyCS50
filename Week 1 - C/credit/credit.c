#include <cs50.h>
#include <stdio.h>



int len(long num);
string check_sum(long credit);


int main(void)
{
    long credit = get_long("Number: ");
    printf("%s", check_sum(credit));
}

string check_sum(long credit)
{
    // Make array and fill with individual digits

    int length = len(credit);
    int digits[length];
    int i = 0;
    while (credit > 0)
    {
        digits[i] = credit % 10;
        credit = (credit - digits[i]) / 10;
        i++;
    }


    // iterate through digits and calculate checksum
    int second_sum = 0;
    int first_sum = 0;
    for (int y = 0; y < sizeof(digits) / sizeof(digits[0]); y++)
    {
        if (y % 2 == 1)
        {
            int digit = digits[y] * 2;
            if (digit >= 10)
            {
                second_sum = second_sum + digit % 10 + 1;
            }
            else
            {
                second_sum = second_sum + digit;
            }
        }
        else if (y % 2 == 0)
        {
            first_sum = first_sum + digits[y];
        }
    }
    int check_sum = first_sum + second_sum;

    // Check Card Type and Validity comparing first (or last depending on perspective) digits in array
    if (check_sum % 10 == 0) // only execute is check_sum is valid
    {
        if (length == 15 && digits[length - 1] == 3) //American Express Case
        {
            if(digits[length - 2] == 4 || digits[length - 2] == 7)
            {
                return "AMEX\n";
            }
            else
            {
                return "INVALID\n";
            }
        }
        if (length == 16) // MasterCard / VISA Case
        {
            if (digits[length - 1] == 5)  //MasterCard Case
            {
                if(digits[length - 2] == 1 || digits[length - 2] == 2 || digits[length - 2] == 3 || digits[length - 2] == 4
                 || digits[length - 2] == 5)
                {
                    return "MASTERCARD\n";
                }
                else
                {
                    return "INVALID\n";
                }
            }
            if (digits[length - 1] == 4) // VISA Case I
            {
                return "VISA\n";
            }
            else
            {
                return "INVALID\n";
            }
        }
        if (length == 13 && digits[length - 1] == 4) //VISA Case II
        {
            return "VISA\n";
        }
        else
        {
            return "INVALID\n";
        }
    }
    return "INVALID\n";
}






int len(long num)
{
    int count = 0;
    int digit = 0;

    while (num > 0)
    {
        digit = num % 10;
        num = (num - digit)/10;
        count ++;
    }
    return count;
}