/** Problem

Given an integer, write a function to determine if it is a power of three.

Follow up:
Could you do it without using any loop / recursion?

*/ 


/*  Algorithm Outline

    Use recursion/loop to judge n/3
    
*/

class Solution 
{
    public:
    
    bool isPowerOfThree(int n)
    {
        if(n <= 0)
        {
            return false;
        }
        
        while(n>1)
        {
            if( n % 3 == 0)
            {
                n = n/3;
            }
            else 
            {
                return false;
            }
        }
        return (n==1);
    }
};