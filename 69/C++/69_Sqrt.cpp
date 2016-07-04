/** Problem

Implement int sqrt(int x).

Compute and return the square root of x.

*/

/** Algorithm Outline

    1. We use binary search
    2. When we compute the square of an integer x, i.e., x^2,  it is easy to overflow. 
       e.g.
       
       int x;
       long long y = x*x; //overflow happend
    
       Therefore, we should not use  "int x", but use "long long x".
       In this case, "x*x" will be long long and will not be overflowed. E.g.,
       
       long long x;
       long long y = x*x //okay 
*/ 

class Solution 
{
    public:
    
    int mySqrt(int x) 
    {
        if(x == 0)
        {
            return 0;
        }
        else if(x == 1)
        {
            return 1;
        }
        
        long long min=1;
        long long max=x;
        long long mid;
        while(min < max)
        {
            mid = (min+max)/2;
            long long temp = mid*mid; //here it is the reason taht we should use "long long mid" to avoid overflow
            if(temp == x)
            {
                return mid;
            }
            else if(temp < x)
            {
                long long  temp2 = (mid+1)*(mid+1); 
                if(temp2 > x )
                {
                    return mid;
                }
                else if(temp2 == x)
                {
                    return mid+1;
                }
                else
                {
                    min=mid+1;
                }
            }
            else //mid*mid > x
            {
                long long temp2 = (mid-1)*(mid-1);
                if( temp2 <= x )
                {
                    return mid-1;
                }
                else
                {
                    max = mid - 1;
                }
            }
        }
        
        //fake return
        return min;
        
    }
};


