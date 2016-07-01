/** Problem


Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example:
Given a = 1 and b = 2, return 3.

*/

/** Algorithm Outline


*/


class Solution 
{
    public:

    int getSum(int a, int b) 
    {
        int sum = a ^ b;
        int carry = a & b;
        while (carry != 0)
        {
            carry = carry << 1;
            a = sum;
            b = carry;
            sum = a ^ b;
            carry = a & b;
        }
        
        return sum;
        
    }
};