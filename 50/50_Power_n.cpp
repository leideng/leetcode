/** Problem

Implement pow(x, n).

*/

/** Algorithm Outline
    1. Use the following equation: 
           pow(x,2n) = pow(x,n)*pow(x,n). We only need to calculate pow(x,n) once
           pow(x, 2n+1) = pow(x,n)*pow(x,n)*x. Again We only need to calculate pow(x,n) once
    2. Carefully handle overflow. Note that:
           std::numeric_limits<int>::max()+1 will be negative (overflowed)
           std::numeric_limits<int>::min()-1 will be negative (overflowed)
*/

class Solution 
{
    public:
    
    double myPow(double x, int n) 
    {
        cout <<  std::numeric_limits<int>::max() << endl;  //2147483647
        cout <<  std::numeric_limits<int>::min() << endl;  //-2147483648
        
        if(n >= 0)
        {
            return power_n(x,n);
        }
        else
        {
            return 1.0/(x*power_n(x,-(n+1)));  //do not use power_n(x,-n), where n=std::numeric_limits<int>::min(), here -2147483648, -n will be negative
        }
        
        //fake return
        return 1.0;
    }
    
    //pow(x, n), n >= 0;
    double power_n(double x, int n)
    {
        if( n == 0)
        {
            return 1.0;
        }
        
        if(n == 1)
        {
            return x;
        }
        
        //n > 1
        if(n % 2 == 0) //n is even
        {
            double v1 = power_n(x,n/2);
            return v1*v1;
        }
        else //n is odd   n = (n-1)/2 + (n+1)/2
        {
            double v2 = power_n(x,(n-1)/2); //do not use (n+1)/2, where n = std::numeric_limits<int>::max(), n+1 will be negative
            return v2*v2*x;
        }
    }
};