/** Problem 

Given two numbers represented as strings, return multiplication of the numbers as a string.

Note:
The numbers can be arbitrarily large and are non-negative.
Converting the input string to integer is NOT allowed.
You should NOT use internal library such as BigInteger.

*/

/** Algorithm Outline

    1. We use the algorithm that we used in elementary school for multiplication
    2. Example:  1234*567 = 1234 * 7 + 12340*6 + 123400*5
*/


class Solution 
{
    public:
    
    string multiply(string num1, string num2) 
    {
        if(num1 == "0" || num2 == "0")
        {
            return "0";
        }
        
        string sum = "0";
        string shifted_num1 = num1;
        for(int j=num2.size()-1; j >= 0 ; --j)
        {
            if(num2[j] != '0')
            {
                sum = add(sum, multiply_int(shifted_num1, num2[j] - '0'));
            }
            shifted_num1 = shifted_num1 + '0'; 
        }
        
        return sum;
    }
    
    string add(string num1, string num2)
    {
        //we first make num1 and num2 with the same length by adding leading zeros
        int num1_size = num1.size();
        int num2_size = num2.size();
        if(num1_size < num2_size) 
        {
            int diff = num2_size - num1_size;
            num1 = string(diff, '0') + num1;
        }
        else if(num1_size > num2_size)
        {
            int diff = num1_size - num2_size;
            num2 = string(diff, '0') + num2;
        }
     
        string sum(num1.size(), '0');
        
        int carry = 0;
        for(int i=num1.size()-1; i >= 0; --i)
        {
            int a = num1[i] - '0';
            int b = num2[i] - '0';
            
            if(a + b + carry >= 10)
            {
                sum[i] = '0' + (a + b + carry - 10);
                carry = 1;
            }
            else
            {
                sum[i] = '0' + (a + b + carry);
                carry = 0;
            }
        }
        
        if(carry == 1)
        {
            sum = '1' + sum;
        }
        
        return sum;
    }
    
    ///y can only be 0,1,2,...,9
    string multiply_int(string num, int y)
    {
        string ret(num.size(), '0');
        
        int carry = 0;
        for(int i=num.size()-1; i >= 0; --i)
        {
            int a = num[i] - '0';
            int prod = a*y + carry;
            if(prod >= 10)
            {
                ret[i] = (prod % 10) + '0';
                carry = prod/10;
            }
            else
            {
                ret[i] = prod + '0';
                carry = 0;
            }
        }
        
        if(carry > 0)
        {
            char c = ('0' + carry);
            ret = c + ret;
        }
        
        return ret;
    }
};